
#include "pre.h"
#include "CMath.h"
#include "CMesh.h"
bool readword(char *line, char *word, char delim)
{
	int max_size = 200;
	char *buf_pos;
	char *start_pos;

	// read past spaces/tabs, or until end of line/string
	for (buf_pos = line; (*buf_pos == ' ' || *buf_pos == '\t') && *buf_pos != '\n' && *buf_pos != '\0';)
		buf_pos++;

	// if end of line/string found, then no words found, return null
	if (*buf_pos == '\n' || *buf_pos == '\0') { *word = '\0'; return false; }

	// mark beginning of word, read until end of word
	for (start_pos = buf_pos; *buf_pos != delim && *buf_pos != '\t' && *buf_pos != '\n' && *buf_pos != '\0';)
		buf_pos++;

	if (*buf_pos == '\n' || *buf_pos == '\0') {    // buf_pos now points to the end of buffer
		//strcpy_s (word, max_size, start_pos);            // copy word to output string
		strncpy(word, start_pos, max_size);
		if (*buf_pos == '\n') *(word + strlen(word) - 1) = '\0';
		*line = '\0';                        // clear input buffer
	}
	else {
		// buf_pos now points to the delimiter after word
		*buf_pos++ = '\0';                    // replace delimiter with end-of-word marker
		//strcpy_s (word, max_size, start_pos);
		strncpy(word, start_pos, buf_pos - line);    // copy word(s) string to output string
		// move start_pos to beginning of entire buffer
		strcpy(start_pos, buf_pos);        // copy remainder of buffer to beginning of buffer
	}
	return true;                        // return word(s) copied
}

void nvMesh::ComputeNormals()
{
	int v1, v2, v3;
	Vector3DF p1, p2, p3;
	Vector3DF norm, side;

	// Clear vertex normals
	for (int n = 0; n < mVertices.size(); n++) {
		mVertices[n].nx = 0;
		mVertices[n].ny = 0;
		mVertices[n].nz = 0;
	}

	// Compute normals of all faces
	int n = 0;
	for (int f = 0; f < mFaces.size(); f++) {
		v1 = mFaces[f].v[0]; v2 = mFaces[f].v[1]; v3 = mFaces[f].v[2];
		p1.Set(mVertices[v1].x, mVertices[v1].y, mVertices[v1].z);
		p2.Set(mVertices[v2].x, mVertices[v2].y, mVertices[v2].z);
		p3.Set(mVertices[v3].x, mVertices[v3].y, mVertices[v3].z);
		norm = p2; norm -= p1; norm.Normalize();
		side = p3; side -= p1; side.Normalize();
		norm.Cross(side);
		mVertices[v1].nx += norm.x; mVertices[v1].ny += norm.y; mVertices[v1].nz += norm.z;
		mVertices[v2].nx += norm.x; mVertices[v2].ny += norm.y; mVertices[v2].nz += norm.z;
		mVertices[v3].nx += norm.x; mVertices[v3].ny += norm.y; mVertices[v3].nz += norm.z;
	}

	// Normalize vertex normals
	Vector3DF vec;
	for (int n = 0; n < mVertices.size(); n++) {
		p1.Set(mVertices[n].nx, mVertices[n].ny, mVertices[n].nz);
		p1.Normalize();
		mVertices[n].nx = p1.x; mVertices[n].ny = p1.y; mVertices[n].nz = p1.z;
	}
}

void nvMesh::AddPlyElement(char typ, int n)
{
	app_printf("  Element: %d, %d\n", typ, n);
	PlyElement* p = new PlyElement;
	if (p == 0x0) { app_printf("ERROR: Unable to allocate PLY element.\n"); }
	p->num = n;
	p->type = typ;
	p->prop_list.clear();
	m_PlyCurrElem = (int)m_Ply.size();
	m_Ply.push_back(p);
}

void nvMesh::AddPlyProperty(char typ, std::string name)
{
	app_printf("  Property: %d, %s\n", typ, name.c_str());
	PlyProperty p;
	p.name = name;
	p.type = typ;
	m_Ply[m_PlyCurrElem]->prop_list.push_back(p);
}
int nvMesh::FindPlyElem(char typ)
{
	for (int n = 0; n < (int)m_Ply.size(); n++) {
		if (m_Ply[n]->type == typ) return n;
	}
	return -1;
}

int nvMesh::FindPlyProp(int elem, std::string name)
{
	for (int n = 0; n < (int)m_Ply[elem]->prop_list.size(); n++) {
		if (m_Ply[elem]->prop_list[n].name.compare(name) == 0)
			return n;
	}
	return -1;
}

bool nvMesh::LoadPly(char* fname, float scal)
{
	FILE* fp;

	int m_PlyCnt;
	float m_PlyData[40];
	char buf[1000];
	char bword[200];
	std::string word;
	int vnum, fnum, elem, cnt;
	char typ;

	localPos = 0;
	localNorm = 1;
	localUV = 2;

	fp = fopen(fname, "rt");
	if (fp == 0x0) { app_printf("ERROR: Could not find mesh file: %s\n", fname); }

	// Read header
	fgets(buf, 1000, fp);
	readword(buf, bword, ' '); word = bword;
	if (word.compare("ply") != 0) {
		app_printf("ERROR: Not a ply file. %s\n", fname);
	}

	m_Ply.clear();

	app_printf("Reading PLY mesh: %s.\n", fname);
	while (feof(fp) == 0) {
		fgets(buf, 1000, fp);
		readword(buf, bword, ' ');
		word = bword;
		if (word.compare("comment") != 0) {
			if (word.compare("end_header") == 0) break;
			if (word.compare("property") == 0) {
				readword(buf, bword, ' ');
				word = bword;
				if (word.compare("float") == 0)		typ = PLY_FLOAT;
				if (word.compare("float16") == 0)	typ = PLY_FLOAT;
				if (word.compare("float32") == 0)	typ = PLY_FLOAT;
				if (word.compare("int8") == 0)		typ = PLY_INT;
				if (word.compare("uint8") == 0)		typ = PLY_UINT;
				if (word.compare("list") == 0) {
					typ = PLY_LIST;
					readword(buf, bword, ' ');
					readword(buf, bword, ' ');
				}
				readword(buf, bword, ' ');
				word = bword;
				AddPlyProperty(typ, word);
			}
			if (word.compare("element") == 0) {
				readword(buf, bword, ' ');    word = bword;
				if (word.compare("vertex") == 0) {
					readword(buf, bword, ' ');
					vnum = atoi(bword);
					app_printf("  Verts: %d\n", vnum);
					AddPlyElement(PLY_VERTS, vnum);
				}
				if (word.compare("face") == 0) {
					readword(buf, bword, ' ');
					fnum = atoi(bword);
					app_printf("  Faces: %d\n", fnum);
					AddPlyElement(PLY_FACES, fnum);
				}
			}
		}
	}

	// Read data
	int xi, yi, zi, ui, vi;
	app_printf("Reading verts..\n");
	elem = FindPlyElem(PLY_VERTS);
	xi = FindPlyProp(elem, "x");
	yi = FindPlyProp(elem, "y");
	zi = FindPlyProp(elem, "z");
	ui = FindPlyProp(elem, "s");
	vi = FindPlyProp(elem, "t");
	if (elem == -1 || xi == -1 || yi == -1 || zi == -1) {
		app_printf("ERROR: Vertex data not found.\n");
	}

	xref vert;
	for (int n = 0; n < m_Ply[elem]->num; n++) {
		fgets(buf, 1000, fp);
		for (int j = 0; j < (int)m_Ply[elem]->prop_list.size(); j++) {
			readword(buf, bword, ' ');
			m_PlyData[j] = (float)atof(bword);
		}
		vert = AddVert(m_PlyData[xi] * scal, m_PlyData[yi] * scal, m_PlyData[zi] * scal, m_PlyData[ui], m_PlyData[vi]);
	}

	app_printf("Reading faces..\n");
	elem = FindPlyElem(PLY_FACES);
	xi = FindPlyProp(elem, "vertex_indices");
	if (elem == -1 || xi == -1) {
		app_printf("ERROR: Face data not found.\n");
	}
	for (int n = 0; n < m_Ply[elem]->num; n++) {
		fgets(buf, 1000, fp);
		m_PlyCnt = 0;
		for (int j = 0; j < (int)m_Ply[elem]->prop_list.size(); j++) {
			if (m_Ply[elem]->prop_list[j].type == PLY_LIST) {
				readword(buf, bword, ' ');
				cnt = atoi(bword);
				m_PlyData[m_PlyCnt++] = (float)cnt;
				for (int c = 0; c < cnt; c++) {
					readword(buf, bword, ' ');
					m_PlyData[m_PlyCnt++] = (float)atof(bword);
				}
			}
			else {
				readword(buf, bword, ' ');
				m_PlyData[m_PlyCnt++] = (float)atof(bword);
			}
		}
		if (m_PlyData[xi] == 3) {
			//debug.Printf ( "    Face: %d, %d, %d\n", (int) m_PlyData[xi+1], (int) m_PlyData[xi+2], (int) m_PlyData[xi+3] );
			AddFace((int)m_PlyData[xi + 1], (int)m_PlyData[xi + 2], (int)m_PlyData[xi + 3]);
		}

		if (m_PlyData[xi] == 4) {
			//debug.Printf ( "    Face: %d, %d, %d, %d\n", (int) m_PlyData[xi+1], (int) m_PlyData[xi+2], (int) m_PlyData[xi+3], (int) m_PlyData[xi+4]);
			// AddFace ( (int) m_PlyData[xi+1], (int) m_PlyData[xi+2], (int) m_PlyData[xi+3], (int) m_PlyData[xi+4] );
		}
	}
	for (int n = 0; n < (int)m_Ply.size(); n++) {
		delete m_Ply[n];
	}
	m_Ply.clear();
	m_PlyCurrElem = 0;

	app_printf("Computing normals.\n");
	ComputeNormals();
	app_printf("Updating VBOs.\n");
	UpdateVBO();

	return 1;
}

int nvMesh::AddVert(float x, float y, float z, float tx, float ty)
{
	Vertex v;
	v.x = x; v.y = y; v.z = z;
	v.nx = v.x; v.ny = v.y; v.nz = v.z;
	float d = v.nx*v.nx + v.ny*v.ny + v.nz*v.nz;
	if (d > 0) { d = sqrt(d); v.nx /= d; v.ny /= d; v.nz /= d; }

	v.tx = v.nx*0.5 + 0.5; v.ty = v.nz + 0.5 + 0.5;

	mVertices.push_back(v);
	return mVertices.size() - 1;
}

int  nvMesh::AddFace(int v0, int v1, int v2)
{
	Face f;
	f.v[0] = v0;
	f.v[1] = v1;
	f.v[2] = v2;
	mFaces.push_back(f);
	return mFaces.size() - 1;
}

void nvMesh::UpdateVBO()
{
#ifdef USE_DX

#else		
	if (mVBO.size() == 0) {
		mVBO.push_back(-1);		// vertex buffer
		mVBO.push_back(-1);		// face buffer
	}
	else {
		glDeleteBuffers(1, &mVBO[0]);
		glDeleteBuffers(1, &mVBO[1]);
	}

	glGenBuffers(1, &mVBO[0]);
	glGenBuffers(1, &mVBO[1]);
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	int numv = mVertices.size();
	int numf = mFaces.size();

	glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, numv * sizeof(Vertex), &mVertices[0].x, GL_STATIC_DRAW_ARB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(localPos, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(localNorm, 3, GL_FLOAT, false, sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(localUV, 2, GL_FLOAT, false, sizeof(Vertex), (void*)24);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numf*sizeof(Face), &mFaces[0], GL_STATIC_DRAW_ARB);

	glBindVertexArray(0);

#endif
}

void nvMesh::SelectVBO()
{
#ifdef USE_DX

#else
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
#endif
}
void nvMesh::Draw()
{
#ifdef USE_DX

#else
	glDrawElements(GL_TRIANGLES, mFaces.size() * 3, GL_UNSIGNED_INT, 0);
#endif
}





