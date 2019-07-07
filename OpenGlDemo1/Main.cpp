#include<gl/GLUT.H>
void myFirstOpenGl(int argc, char *argv[]);
const int win_w = 700, win_h = 700;
GLfloat modelview_matrix[16];
GLfloat edefault_matrix[16];
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
	// 前后，周围漫射.....
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

}
void Initial(void)//初始化函数 
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
	//glBitmap();*/
	glFlush();//清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
}
int main(int argc, char * argv[])//这是使用glut库函数进行窗口管理
{
	myFirstOpenGl( argc, argv);
	return 0;
}
// 初始化设置
void myFirstOpenGl(int argc, char *argv[])
{

	glutInit(&argc, argv);//使用glut库需要进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设定窗口显示模式，颜色模型和缓存，这里是RGB颜色模型和单缓存
	glutInitWindowPosition(100, 100);//设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(400, 400);//设定窗口的大小
	glutCreateWindow("第一个OpenGL程序——邓芮");//创建一个窗口，参数是窗口标题名
	glutDisplayFunc(&myDisplay);//将myDisplay指定为当前窗口的显示内容函数
	Initial();
	glutMainLoop();//使窗口框架运行起来，使显示回调函数开始工作

}