#include "CGUI.h"



//--------------------------------------- 2D GUIs

nvGui::nvGui()
{
	mActiveGui = -1;
}

int nvGui::AddGui(float x, float y, float w, float h, char* name, int gtype, int dtype, void* data, float vmin, float vmax)
{
	Gui g;

	g.name = name;
	g.x = x; g.y = y;
	g.w = w; g.h = h;
	g.gtype = gtype;
	g.dtype = dtype;
	g.data = data;
	g.vmin = vmin;
	g.vmax = vmax;

	mGui.push_back(g);
	return mGui.size() - 1;
}
bool nvGui::guiChanged(int n)
{
	if (n < 0 || n >= mGui.size()) return false;
	if (mGui[n].changed) {
		mGui[n].changed = false;
		return true;
	}
	return false;
}

void nvGui::Draw()
{
	char buf[1024];
	float x1, y1, x2, y2, frac, dx;
	bool bval;

	start2D();

	for (int n = 0; n < mGui.size(); n++) {

		x1 = mGui[n].x;	y1 = mGui[n].y;
		x2 = x1 + mGui[n].w; y2 = y1 + mGui[n].h;

		switch (mGui[n].gtype) {
		case GUI_PRINT: {
			switch (mGui[n].dtype) {
			case GUI_INT:	sprintf(buf, "%d", *(int*)mGui[n].data);	break;
			case GUI_FLOAT: sprintf(buf, "%.5f", *(float*)mGui[n].data);	break;
			case GUI_BOOL:  if (*(bool*)mGui[n].data) sprintf(buf, "on"); else sprintf(buf, "off");	break;
			};
			dx = getTextX(buf);
			drawText(x2 - dx, y1 + 10, buf, .9f, .9f, .9f, 1.0f);
			sprintf(buf, "%s", mGui[n].name.c_str());
			drawText(x1, y1 + 10, buf, 1, 1, 1, 1);
		} break;
		case GUI_SLIDER: {
			drawFill(x1, y1 + 12, x2, y2, .3f, .3f, .3f, 1.0f);
			switch (mGui[n].dtype) {
			case GUI_INT:	frac = (float(*(int  *)mGui[n].data) - mGui[n].vmin) / (mGui[n].vmax - mGui[n].vmin); sprintf(buf, "%d", *(int*)mGui[n].data);	break;
			case GUI_FLOAT: frac = ((*(float*)mGui[n].data) - mGui[n].vmin) / (mGui[n].vmax - mGui[n].vmin); sprintf(buf, "%.3f", *(float*)mGui[n].data);	break;
			};
			drawFill(x1, y1 + 12, x1 + frac*(x2 - x1), y2, .6f, 1.0f, .8f, 1.0f);
			dx = getTextX(buf);
			drawText(x2 - dx, y1 + 10, buf, 1.0f, 1.0f, 1.0f, 1.0f);
			sprintf(buf, "%s", mGui[n].name.c_str());
			drawText(x1, y1 + 10, buf, 1, 1, 1, 1);
		} break;
		case GUI_CHECK: {
			drawRect(x2 - 10, y1, x2, y1 + 10, .8f, .8f, .8f, 1.0f);
			switch (mGui[n].dtype) {
			case GUI_INT:		bval = (*(int*)mGui[n].data) == 0 ? false : true;	break;
			case GUI_FLOAT:		bval = (*(float*)mGui[n].data) == 0.0 ? false : true;	break;
			case GUI_BOOL:		bval = *(bool*)mGui[n].data;	break;
			};
			if (bval) {
				drawText(x2 - 40, y1 + 10, "on", .6f, 1.0f, .8f, 1.0f);
				drawLine(x2 - 10, y1, x2, y1 + 10, .6f, 1.0f, .8f, 1.0f);
				drawLine(x2 - 10, y1 + 10, x2, y1, .6f, 1.0f, .8f, 1.0f);
			}
			else {
				drawText(x2 - 40, y1 + 10, "off", .8f, .8f, .8f, 1.0f);
			}
			sprintf(buf, "%s", mGui[n].name.c_str());
			drawText(x1, y1 + 10, buf, 1.0f, 1.0f, 1.0f, 1.0f);
		} break;
		}
	}
	end2D();

}

bool nvGui::MouseDown(float x, float y)
{
	// GUI down - Check if GUI is hit
	float x1, y1, x2, y2;
	for (int n = 0; n < mGui.size(); n++) {
		x1 = mGui[n].x;			y1 = mGui[n].y;
		x2 = x1 + mGui[n].w;	y2 = y1 + mGui[n].h;
		switch (mGui[n].gtype) {
		case GUI_SLIDER:
			if (x > x1 && x < x2 && y > y1 && y < y2) {
				mActiveGui = n;	  	// set active gui				
				return true;
			}
			break;
		case GUI_CHECK:
			if (x > x2 - 10 && x < x2 && y > y1 && y < y1 + 10) {
				mActiveGui = -1;
				mGui[n].changed = true;
				switch (mGui[n].dtype) {
				case GUI_INT:	*(int*)mGui[n].data = ((*(int*)mGui[n].data) == 0) ? 1 : 0;			break;
				case GUI_FLOAT:	*(float*)mGui[n].data = ((*(int*)mGui[n].data) == 0.0) ? 1.0 : 0.0;	break;
				case GUI_BOOL:	*(bool*)mGui[n].data = !(*(bool*)mGui[n].data);		break;
				};
				return true;
			}
			break;
		default: break;
		};
	}
	mActiveGui = -1;
	return false;
}

bool nvGui::MouseDrag(float x, float y)
{
	// GUI drag - Adjust value of hit gui
	float x1, y1, x2, y2;
	if (mActiveGui != -1) {
		x1 = mGui[mActiveGui].x;			y1 = mGui[mActiveGui].y;
		x2 = x1 + mGui[mActiveGui].w;	y2 = y1 + mGui[mActiveGui].h;
		if (x <= x1) {
			mGui[mActiveGui].changed = true;
			switch (mGui[mActiveGui].dtype) {
			case GUI_INT:	*(int*)mGui[mActiveGui].data = (int)mGui[mActiveGui].vmin;		break;
			case GUI_FLOAT:	*(float*)mGui[mActiveGui].data = (float)mGui[mActiveGui].vmin;	break;
			};
			return true;
		}
		if (x >= x2) {
			mGui[mActiveGui].changed = true;
			switch (mGui[mActiveGui].dtype) {
			case GUI_INT:	*(int*)mGui[mActiveGui].data = (int)mGui[mActiveGui].vmax;		break;
			case GUI_FLOAT:	*(float*)mGui[mActiveGui].data = (float)mGui[mActiveGui].vmax;	break;
			};
			return true;
		}
		if (x > x1 && x < x2) {
			mGui[mActiveGui].changed = true;
			switch (mGui[mActiveGui].dtype) {
			case GUI_INT:	*(int*)mGui[mActiveGui].data = (int)(mGui[mActiveGui].vmin + (x - x1)*mGui[mActiveGui].vmax / (x2 - x1));		break;
			case GUI_FLOAT:	*(float*)mGui[mActiveGui].data = (float)(mGui[mActiveGui].vmin + (x - x1)*mGui[mActiveGui].vmax / (x2 - x1));	break;
			};
			return true;
		}
	}
	return false;
}
