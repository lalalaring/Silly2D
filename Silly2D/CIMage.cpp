#include "CImage.h"


/*void save_png ( char* fname, unsigned char* img, int w, int h )
{
unsigned error = lodepng::encode ( "test.png", img, w, h );
if (error) printf ( "png write error: %s\n", lodepng_error_text(error) );
}*/

void nvImg::Create(int x, int y, int fmt)
{
	mXres = x;
	mYres = y;
	mSize = mXres * mYres;
	mFmt = fmt;

	switch (mFmt) {
	case IMG_RGB:  mSize *= 3;	break;
	case IMG_RGBA: mSize *= 4; break;
	case IMG_LUM:  break;
	}

	if (mData != 0x0) free(mData);
	mData = (unsigned char*)malloc(mSize);

	memset(mData, 0, mSize);

	UpdateTex();
}

void nvImg::Fill(float r, float g, float b, float a)
{
	unsigned char* pix = mData;
	for (int n = 0; n < mXres*mYres; n++) {
		*pix++ = r*255.0f; *pix++ = g*255.0f; *pix++ = b*255.0f; *pix++ = a*255.0f;
	}
	UpdateTex();
}

bool nvImg::LoadPng(char* fname)
{
	std::vector<unsigned char> out;
	unsigned int w, h;

	app_printf("Reading PNG: %s\n", fname);
	unsigned error = lodepng::decode(out, w, h, fname);
	if (error) {
		app_printf("png read error: %s\n", lodepng_error_text(error));
		return false;
	}
	mXres = w;
	mYres = h;
	mSize = w*h * 4;
	mFmt = IMG_RGBA;
	if (mData != 0x0)  free(mData);
	mData = (unsigned char*)malloc(mSize);

	memcpy(mData, &out[0], mSize);
	//memset ( mData, 128, mSize );

	UpdateTex();

	return true;
}

bool nvImg::LoadTga(char* fname)
{
	app_printf("Reading TGA: %s\n", fname);
	TGA* fontTGA = new TGA;
	TGA::TGAError err = fontTGA->load(fname);
	if (err != TGA::TGA_NO_ERROR) {
		delete fontTGA;
		return false;
	}

	mXres = fontTGA->m_nImageWidth;
	mYres = fontTGA->m_nImageHeight;
	mSize = mXres * mYres;

	switch (fontTGA->m_texFormat) {
	case TGA::RGB:		mFmt = IMG_RGB;		mSize *= 3;	break;
	case TGA::RGBA:		mFmt = IMG_RGBA;	mSize *= 4; break;
	case TGA::ALPHA:	mFmt = IMG_LUM;					break;
	}

	if (mData != 0x0) free(mData);
	mData = (unsigned char*)malloc(mSize);

	memcpy(mData, fontTGA->m_nImageData, mSize);

	UpdateTex();

	delete fontTGA;

	return true;
}


void nvImg::UpdateTex()
{
#ifdef USE_DX

#else
	if (mTex != -1) glDeleteTextures(1, (GLuint*)&mTex);

	app_printf(" Updating Texture %d x %d\n", mXres, mYres);
	glGenTextures(1, (GLuint*)&mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum fmt;
	switch (mFmt) {
	case IMG_RGB:	fmt = GL_RGB; break;
	case IMG_RGBA:	fmt = GL_RGBA; break;
	case IMG_LUM:	fmt = GL_LUMINANCE; break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, fmt, mXres, mYres, 0, fmt, GL_UNSIGNED_BYTE, mData);
#endif
}