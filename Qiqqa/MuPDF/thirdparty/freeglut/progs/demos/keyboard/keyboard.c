#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <GL/freeglut.h>

static void display(void);
static void draw_text(int x, int y, const char *str);
static const char *skeyname(int skey);
static void reshape(int x, int y);
static void keypress(unsigned char key, int x, int y);
static void keyrelease(unsigned char key, int x, int y);
static void skeypress(int key, int x, int y);
static void skeyrelease(int key, int x, int y);

static unsigned int modstate;
static int cur_key = -1;
static int cur_skey = -1;
static int win_width, win_height;



#if defined(BUILD_MONOLITHIC)
#define main      fg_keyboard_demo_main
#endif

int main(int argc, const char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 200);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Keyboard demo");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keypress);
	glutKeyboardUpFunc(keyrelease);
	glutSpecialFunc(skeypress);
	glutSpecialUpFunc(skeyrelease);

	glutMainLoop();
	return 0;
}

static void display(void)
{
	char str[256];

	glClear(GL_COLOR_BUFFER_BIT);

	strcpy(str, "Key:");
	if(cur_key > 0) {
		if(isprint(cur_key)) {
			sprintf(str + 4, " '%c'", cur_key);
		} else {
			sprintf(str + 4, " 0x%02x", cur_key);
		}


		if(modstate & GLUT_ACTIVE_SHIFT) {
			strcat(str, "  shift");
		}
		if(modstate & GLUT_ACTIVE_CTRL) {
			strcat(str, "  ctrl");
		}
		if(modstate & GLUT_ACTIVE_ALT) {
			strcat(str, "  alt");
		}
		if(modstate & GLUT_ACTIVE_SUPER) {
			strcat(str, "  super");
		}
	}
	draw_text(win_width / 3, 2 * win_height / 3, str);

	strcpy(str, "Special key: ");
	if(cur_skey > 0) {
		strcat(str, skeyname(cur_skey));
	}
	draw_text(win_width / 3, win_height / 3, str);

	glutSwapBuffers();
}

static void draw_text(int x, int y, const char *str)
{
	glRasterPos2i(x, y);
	while(*str) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);
	}
}

static const char *skeyname(int skey)
{
	static const char *fkeys[] = {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12"};

	switch(skey) {
	case GLUT_KEY_LEFT: return "left";
	case GLUT_KEY_UP: return "up";
	case GLUT_KEY_RIGHT: return "right";
	case GLUT_KEY_DOWN: return "down";
	case GLUT_KEY_PAGE_UP: return "page up";
	case GLUT_KEY_PAGE_DOWN: return "page down";
	case GLUT_KEY_HOME: return "home";
	case GLUT_KEY_END: return "end";
	case GLUT_KEY_INSERT: return "insert";
	case GLUT_KEY_NUM_LOCK: return "num lock";
	case GLUT_KEY_BEGIN: return "begin";
	case GLUT_KEY_DELETE: return "delete";
	case GLUT_KEY_SHIFT_L: return "L Shift";
	case GLUT_KEY_SHIFT_R: return "R Shift";
	case GLUT_KEY_CTRL_L: return "L Ctrl";
	case GLUT_KEY_CTRL_R: return "R Ctrl";
	case GLUT_KEY_ALT_L: return "L Alt";
	case GLUT_KEY_ALT_R: return "R Alt";
	case GLUT_KEY_SUPER_L: return "L Super";
	case GLUT_KEY_SUPER_R: return "R Super";
	default:
		if(skey >= GLUT_KEY_F1 && skey <= GLUT_KEY_F12) {
			return fkeys[skey - GLUT_KEY_F1];
		}

		break;
	}
	return "<unknown>";
}

static void reshape(int x, int y)
{
	win_width = x;
	win_height = y;
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, 0, y, -1, 1);
}

static void keypress(unsigned char key, int x, int y)
{
	if(key == 27) exit(0);

	modstate = glutGetModifiers();
	cur_key = key;
	glutPostRedisplay();
}

static void keyrelease(unsigned char key, int x, int y)
{
	cur_key = -1;
	glutPostRedisplay();
}

static void skeypress(int key, int x, int y)
{
	cur_skey = key;
	glutPostRedisplay();
}

static void skeyrelease(int key, int x, int y)
{
	cur_skey = -1;
	glutPostRedisplay();
}
