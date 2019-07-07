#include<gl/GLUT.H>
#include<stdio.h>
#include<iostream>
using namespace std;
void myFirstOpenGl(int argc, char *argv[]);
const int win_w = 700, win_h = 700;
GLfloat modelview_matrix[16];
GLfloat default_matrix[16];
GLfloat modelview_z_dis;
GLfloat x_min = .0, x_max = 20.0, y_min = .0, y_max = 20.0, z_min = .0, z_max = 20.0;
void xyz_line(float len)
{
	GLfloat color[] = { .0,.0,.0,1.0 };
	// 材质设置，指明在设置材质的哪个表面的颜色
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	// 表示一组用于定义一个或者多个图元的顶点的开始，通常玉glEnd一起用，两者之间可调用一些函数
	glBegin(GL_LINES);
	// 设置颜色
	color[0] = 1.0; color[1] = .0; color[2] = .0;
	// 前后，周围漫射
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(len, .0,.0);
	color[0] = .0; color[1] = 1.0; color[2] = .0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, len, .0);
	color[0] = .0; color[1] = .0; color[2] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, .0, len);
	glEnd();
}
void draw()
{
	// 绘制一个灰色的球
	GLfloat color[] = { .4f,.4f,.4f,1.0f };
	// 反射
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

	// 这个函数告诉接下来要做什么的声明，参数有三种模式：
	// GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理
	glMatrixMode(GL_MODELVIEW);
	// 保存当前矩阵
	glPushMatrix();
	glTranslatef(8.0, 5.0, 8.0);
	glutSolidSphere(5., 30, 50);
	glPopMatrix();

	// 绘制一面镜子
	color[0] = 1.0;color[1] = 1.0;color[2] = 1.0;color[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
	color[0] = .0f;color[1] = .0f;color[2] = .1f;color[3] = 1.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(.0, 20.0, .0);
	glBegin(GL_MODELVIEW);
	glNormal3f(.0, -1.0, .0);
	glVertex3f(.0, .0, .0);
	glVertex3f(20.0, .0, .0);
	glVertex3f(20.0, .0, 20.0);
	glVertex3f(.0, .0, 20.0);
	glEnd();
	// 删除矩阵
	glPopMatrix();

	// 绘制两个三角形
	color[0] = .0;color[1] = .0;color[2] = .0;color[3]=1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

	glBegin(GL_TRIANGLES);
	color[0] = .0f;color[1] = .8f;color[2] = .8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glNormal3f(1.0, .0, .0);
	glVertex3f(.0, .0, .0);
	glVertex3f(.0, 15.0, .0);
	glVertex3f(.0, .0, 30.0);
	glEnd();

	// 透明物体放到所有不透明物体后绘制（否则不会混合），并置深度缓冲只读（否则会遮挡之后物体）
	glDepthMask(GL_FALSE);
	// 绘制三角形
	glBegin(GL_TRIANGLES);
	color[0] = 1.0;color[1] = 1.0;color[2] = .0;color[3] = 0.5;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	glNormal3f(.0, .0, 1.0);
	glVertex3f(.0, .0, .0);
	glVertex3f(10.0, .0, .0);
	glVertex3f(.0, 20.0, .0);
	glEnd();
	glDepthMask(GL_TRUE);

}
// 显示函数
void display_func()
{
	static int z = 0;
	std:: cout<< "display:" << z++ << std::endl;
	// 表示要清除颜色缓冲以及深度缓冲，可以使用以下标志位
	// GL_COLOR_BUFFER_BIT:    当前可写的颜色缓冲
    // GL_DEPTH_BUFFER_BIT:    深度缓冲
	// GL_ACCUM_BUFFER_BIT : 累积缓冲
	// GL_STENCIL_BUFFER_BIT : 模板缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	// 设置当前矩阵
	glLoadMatrixf(modelview_matrix);

	draw();
	xyz_line(40.0);
	// 交换两个缓冲区的指针，当绘制完成，将结果显示在屏幕上，从而解决频繁刷新导致的画面闪烁问题
	glutSwapBuffers();

}
// 初始化opengl
void init()
{
	// 投影矩阵初始化
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 10.0, 300.0);
	// 默认矩阵初始化
	glMatrixMode(GL_MODELVIEW);
	// 对当前矩阵进行初始化
	glLoadIdentity();
	/*函数原型
		void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz);
	该函数定义一个视图矩阵，并与当前矩阵相乘。
		第一组eyex, eyey, eyez 相机在世界坐标的位置
		第二组centerx, centery, centerz 相机镜头对准的物体在世界坐标的位置
		第三组upx, upy, upz 相机向上的方向在世界坐标中的方向
		你把相机想象成为你自己的脑袋：
		第一组数据就是脑袋的位置
		第二组数据就是眼睛看的物体的位置
		第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）*/
	gluLookAt(100.0 + (x_min + x_max)*.5, 100.0 + (y_min + y_max)*.5, 100.0 + (z_min + z_max)*.5,
		(x_min + x_max)*.5, (y_min + y_max)*.5, (z_min + z_max)*.5, .0, .0, 1.0);
	modelview_z_dis= 100.0f * sqrt(3.0f);
	//这个函数的作用是取出GL_MODELVIEW_MATRIX，然后存储在mat这个矩阵中，用于逆变换等
	glGetFloatv(GL_MODELVIEW_MATRIX, default_matrix);
	// 将default拷贝到modelview中，sizeof表示拷贝大小
	memcpy(modelview_matrix, default_matrix,sizeof(default_matrix));
	glLoadIdentity();
	// 设置颜色和光线
	glClearColor(.2f, .2f, .2f, 1.0f);
	glColor4f(.5f, .5f, .5f, 1.0f);
	glShadeModel(GL_SMOOTH);
	
	GLfloat vec4f[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, vec4f);  // 光源散射颜色，纯白
	glLightfv(GL_LIGHT0, GL_SPECULAR, vec4f); // 光源镜面颜色，纯白
	vec4f[0] = .1f; vec4f[1] = .1f; vec4f[2] = .1f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, vec4f);  // 光源环境强度，灰色（0.1 强度白色）
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // 有限远观察点
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);     // 双面光照
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = .0;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vec4f);	// 全局环境光，黑色（无光）

	vec4f[0] = .0; vec4f[1] = modelview_z_dis; vec4f[2] = .0; vec4f[3] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, vec4f); // 位置式光源，位置在物体斜上方
	vec4f[0] = .0; vec4f[1] = .0; vec4f[2] = -1.0;
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, vec4f); // 光源发光方向

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE); // 使能自动规范化法线向量，保证光照计算的正确性
}
/*void Initial(void)//初始化函数 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//白色背景，前3个是RGB，最后是Alpha值，用来控制透明，1.0表示完全不透明
	glMatrixMode(GL_PROJECTION);//OpenGL按照三维方式来处理图像，所以需要一个投影变换将三维图形投影到显示器的二维空间中
	gluOrtho2D(0.0, 200, 0.0, 150.0);//指定使用正投影将一个x坐标在0~200，y坐标0~150范围内的矩形坐标区域投影到显示器窗口

}
void myDisplay(void)//显示回调函数
{
	xyz_line(40.0);
	/*glClear(GL_COLOR_BUFFER_BIT);//使用glClearColorz中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色
	glColor3f(1.0f, 0.0f, 0.0f);//绘图颜色为橘黄色
	glRectf(50.0f, 100.0f, 150.0f, 50.0f);//图形的坐标，绘制一个左上角在（50，100），右下角在（150，50）的矩形
	//glBitmap();
	glFlush();//清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
}*/

void reshape_func(int w, int h);
void display_func();
void mouse_click_func(int button, int state, int x, int y);
void mouse_move_func(int x, int y);
void keyboard_func(unsigned char key, int x, int y);
void specialkey_func(int key, int x, int y);
int main(int argc, char * argv[])//这是使用glut库函数进行窗口管理
{
	//myFirstOpenGl( argc, argv);
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutInitWindowSize(win_w, win_h);
	glutInitWindowPosition(300, 0);
	glutCreateWindow("glut test");
	// The callbacks.
	glutReshapeFunc(reshape_func);
	glutDisplayFunc(display_func);
	glutMouseFunc(mouse_click_func);
	glutMotionFunc(mouse_move_func);
	glutKeyboardFunc(keyboard_func);
	glutSpecialFunc(specialkey_func);
	init();
	glutMainLoop();
	return 0;
	return 0;
}
// 窗口大小改变的响应函数
void reshape_func(int w, int h)
{
	glViewport(0, h - win_w, win_w, win_h);
}
/* 以下三个函数对物体进行平移、旋转、缩放，他们均在视觉(绝对)坐标下进行
 * 正常调用 glTranslate,glRotate,glScale 均是在局部坐标下进行(按正序看)
 * 为了达到在视觉坐标下操作的效果，需要将矩阵左乘到当前矩阵
 */
void absolute_translate(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_rotate(GLfloat dgree, GLfloat vecx, GLfloat vecy, GLfloat vecz)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// 平移回去，注意该句和后两句要倒序来看
	glRotatef(dgree, vecx, vecy, vecz);// 积累旋转量
	glTranslatef(.0, .0, modelview_z_dis);		// 先平移到原点
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_scale(GLfloat factor)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(.0, .0, -modelview_z_dis);		// 平移回去，注意该句和后两句要倒序来看
	glScalef(factor, factor, factor);
	glTranslatef(.0, .0, modelview_z_dis);		// 先平移到原点
	glMultMatrixf(modelview_matrix); // 使变换矩阵左乘到当前矩阵，这样才适合绝对坐标的考虑
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glPopMatrix();
}
void absolute_default()
{
	memcpy(modelview_matrix, default_matrix, sizeof(default_matrix));
}

// 鼠标状态变量，用来在鼠标点击事件和拖动事件之间通信
static bool l_button_down = false, r_button_down = false, mid_button_down = false;
static int last_x = -1, last_y = -1;
#define  GLUT_WHEEL_UP		3 // 滚轮操作  
#define  GLUT_WHEEL_DOWN	4
/* 鼠标点击和移动，左键拖动旋转，中键拖动平移，右键回到最初视图
 */
void mouse_click_func(int button, int state, int x, int y)
{
	y = win_h - y;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			l_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		}
		else {
			l_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			mid_button_down = true;
			last_x = x; last_y = y;
			glutSetCursor(GLUT_CURSOR_CYCLE);

		}
		else {
			mid_button_down = false;
			last_x = -1; last_y = -1;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			r_button_down = true;
			absolute_default();
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutPostRedisplay();
		}
		else {
			r_button_down = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		break;
	case GLUT_WHEEL_UP:
		if (state == GLUT_UP) {
			absolute_scale(.9f);
			glutPostRedisplay();
		}
		break;
	case GLUT_WHEEL_DOWN:
		if (state == GLUT_UP) {
			absolute_scale(1.1f);
			glutPostRedisplay();
		}
		break;
	}
}
void mouse_move_func(int x, int y)
{
	y = win_h - y;
	if (last_x >= 0 && last_y >= 0 && (last_x != x || last_y != y)) {
		GLfloat deltax = GLfloat(x - last_x), deltay = GLfloat(y - last_y);
		if (mid_button_down) {
			absolute_translate(deltax * .1f, deltay * .1f, .0f);
			glutPostRedisplay();
		}
		else if (l_button_down) {
			GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
			absolute_rotate(dis, -deltay / dis, deltax / dis, .0);
			glutPostRedisplay();
		}
	}
	last_x = x; last_y = y;
}
/* 键盘按键
 */
void keyboard_func(unsigned char key, int x, int y)
{
	;
}

/* 键盘特殊键，上下键进行上下旋转，左右键进行左右旋转
 */
void specialkey_func(int key, int x, int y)
{
	GLfloat deltax = .0, deltay = .0;
	switch (key) {
	case GLUT_KEY_UP:
		deltay += 1.0;
		break;
	case GLUT_KEY_DOWN:
		deltay -= 1.0;
		break;
	case GLUT_KEY_LEFT:
		deltax -= 1.0;
		break;
	case GLUT_KEY_RIGHT:
		deltax += 1.0;
		break;
	}
	if (abs(deltax) > .0 || abs(deltay) > .0) {
		GLfloat dis = sqrt(deltax*deltax + deltay * deltay);
		absolute_rotate(dis, -deltay / dis, deltax / dis, .0);
		glutPostRedisplay();
	}
}
// 初始化设置
/*void myFirstOpenGl(int argc, char *argv[])
{

	glutInit(&argc, argv);//使用glut库需要进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设定窗口显示模式，颜色模型和缓存，这里是RGB颜色模型和单缓存
	glutInitWindowPosition(100, 100);//设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(400, 400);//设定窗口的大小
	glutCreateWindow("第一个OpenGL程序——邓芮");//创建一个窗口，参数是窗口标题名
	glutDisplayFunc(&myDisplay);//将myDisplay指定为当前窗口的显示内容函数
	Initial();
	glutMainLoop();//使窗口框架运行起来，使显示回调函数开始工作

}*/