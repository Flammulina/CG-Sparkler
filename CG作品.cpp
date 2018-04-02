#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define KEY_ESC 27

//��]�p�xtheta��0.0�ŏ�����
double theta = 0.0;
double theta2 = 0.0;
double theta3 = 0.0;
double fall = 0.0;
int down = 0;

/*-- ���C�g�̃p�����[�^�l�ݒ�@--*/
//GLfloat light0[] = { 0.0, 0.0, 2.0, 1.0 };
GLfloat light1[] = { 0.0, -3.0, -1.0, 0.0 };
GLfloat light2[] = { 0.0, -4.0, 4.0, 1.0 };

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

// ���̕\�ʑ���
GLfloat sphere_diffuse[] = { 1.0, 0.6, 0.1, 1.0 };
GLfloat sphere_specular[] = { 1.0, 0.8, 0.8, 1.0 };
GLfloat sphere_ambient[] = { 0.6, 0.2, 0.2, 1.0 };
// �ΉԂ̕\�ʑ���
GLfloat cube_diffuse[] = { 1.0, 0.8, 0.1, 1.0 };
GLfloat cube_specular[] = { 0.8, 0.8, 0.6, 1.0 };
GLfloat cube_ambient[] = { 0.6, 0.1, 0.2, 1.0 };
// ������̕\�ʑ���
GLfloat long_diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat long_specular[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat long_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

#define	imageWidth 128
#define	imageHeight 128

unsigned char texImage[imageHeight][imageWidth][4];//�e�N�X�`���̈�

//�L�[�{�[�h�C�x���g
//ESC�ŏI���@f�ŗ��� r�Ō��ɖ߂�
void myKeyboard(unsigned char key, int x, int y) {
	if (key == KEY_ESC)
		exit(0);
	if (key == 'f') {
		down = 1;
		fall = 0.0;
	}
	if (key == 'r') {
		down = 0;
		fall = 0.0;
	}
}
void readRAWImage(char* filename)//�e�N�X�`���̓ǂݍ���
{
	FILE *fp;

	if (fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "Cannot open raw file %s\n", filename);
		exit(1);
	}

	fread(texImage, 1, imageWidth*imageHeight * 3, fp);	// read RGB data
	fclose(fp);
}

//�`��֐�
void display(void) {
	GLfloat light0[] = { 0.0, theta, 0.0, 1.0 };//���C�g��y����ω�����悤�ɂ��Č��̃u����\��
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�F�o�b�t�@�ƉB�ʏ���
	glEnable(GL_DEPTH_TEST);//�_�u���o�b�t�@
	glEnable(GL_LIGHTING);//���ݒ�
	//���C�g��ݒu
	glPushMatrix();//1
	glLightfv(GL_LIGHT1, GL_POSITION, light1);
	glLightfv(GL_LIGHT2, GL_POSITION, light2);
	glPushMatrix();//2

	// ���C�g0�̉�]�̃R�[�h�͂�����
	glLightfv(GL_LIGHT0, GL_POSITION, light0);

	glPopMatrix();//2
	glPushMatrix();
	if (down == 1)
		glTranslated(0.0, fall, 0.0);//����
	glPushMatrix();//3
	glPushMatrix();//4
	//�ΉԂ̐F���f
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glRotated(90, 1.0, 1.0, 1.0);
	if (theta3 == 0) {
		glRotated(theta2, 0.0, 1.0, 0.0);
		//�Ήԕ\��
		for (int i = 0; i < 20; i++) {
			glutSolidCube(0.02);
			glTranslated(0.0, 0.0, 0.02);
		}
		glPushMatrix();//5
		for (int i = -140; i < 140; i += 20) {
			glRotated(i + 20, rand() % 2, rand() % 2, rand() % 2);
			glPushMatrix();//6
			for (int j = 0; j < 10; j++) {
				glutSolidCube(0.02);
				glTranslated(0.0, 0.0, 0.02);
			}
			glPopMatrix();//6
		}
		glPopMatrix();//5
	}
	glPopMatrix();//4

	// ���̕\�ʑ���
	glPushMatrix();//7
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sphere_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, sphere_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	glMaterialf(GL_FRONT, GL_EMISSION, 10000);

	glutSolidSphere(0.1, 100, 100);

	glPopMatrix();//7
	glPopMatrix();//3
	glPopMatrix();

	glPushMatrix();//8
	glTranslated(0.0, 3.0, 0.0);
	glRotated(90, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	//�e�N�X�`������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, long_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, long_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, long_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	for (int i = 0; i < 30; i++) {
		glutSolidCube(0.1);
		glTranslated(0.0, 0.0, 0.1);
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();//8



	glPopMatrix();//1

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();

}

//�������֐�
void myInit(char *progname) {
	int width = 500, height = 500;
	float aspect = (float)width / (float)height;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.05, 0.0, 0.05, 1.0);
	glutKeyboardFunc(myKeyboard);

	readRAWImage("CG��i�e�N�X�`��.raw");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);

	/*�������e*/
	gluPerspective(60.0, aspect, 1.0, 10.0);
	/*���_�ύX�iz=5.0���猴�_�����Ă���j*/
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// �A�j���[�V�����̂��߂ɏd�v
	glMatrixMode(GL_MODELVIEW);

	/*-- ���C�g�̐ݒ���L�q --*/
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

//idle�֐�
void idle() {
	// idle�֐���ݒ�
	theta = fmod(theta + 0.5, 3.0);
	theta2 = fmod(theta2 + 20.0, 360.0);
	theta3 = rand() % 3;
	if (down == 1) {
		//fall = fmod(theta2 + 0.3, 1000);
		fall -= 0.02;
	}

	glutPostRedisplay();
}
void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -3.6);
}

//���C���֐�
int main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

