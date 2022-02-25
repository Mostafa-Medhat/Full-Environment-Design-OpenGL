#include <iostream>
using namespace std;
#include <math.h>
#include <GL/glut.h>
#include "imageloader.h"



#define PI 3.14

double eye[] = { 0, 0, 3 };
double center[] = { 0, 0, 2 };
double up[] = { 0, 1, 0 };
static int LeftShoulder_1 = 0, LeftShoulder_2 = 0, LeftShoulder_3 = 0, LeftElbow = 0, RightShoulder_1 = 0, RightShoulder_2 = 0, RightShoulder_3 = 0, RightElbow = 0, LeftPelv_1 = 0, LeftPelv_2 = 0, LeftKnee = 0, RightPelv_1 = 0, RightPelv_2 = 0, RightKnee = 0;
int moving, startx, starty;
static int leftFingersBase = 0, leftFingersUp = 0, leftThmbBase = 0, leftThmbUp = 0, rightFingersBase = 0, rightFingersUp = 0, rightThmbBase = 0, rightThmbUp = 0;
const char* modelname = "data/CHAIR/HUG ARMCHAIR.obj";
const char* modelname2 = "data/soccerball.obj";
const char* floorTexture = "images/grass.bmp";

static float x = 0, y = 0, z = 0.5;
double bodyPos[] = { 0.0,0.5,0.0 };
static int bodyAngleX = 0, bodyAngleY = 0, bodyAngleZ = 0;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
double angle3 = 0.0;
double cp[3];
float modelpos[3] = { 0 ,-0.9 ,-0.7 };
static int ballAngle = 0;



float poses[9][31] = { {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70}
};

float chillPos[9][31] = { {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {15 ,0 ,0 ,-15 ,0 ,0 ,-50 ,-50 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-5 ,0 ,0 ,-0.5 ,0.2 ,-0.4 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70}
};

float backFlipPoses[9][31] = { {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,90 ,0 ,0 ,0.5 ,0,0.5,0.2,0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-10 ,0 ,0 ,-15 ,0 ,0 ,-30 ,0 ,-10 ,0 ,20 ,10 ,-5 ,90 ,15 ,0 ,0.6 ,0,0.5,0.2,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-15 ,-60 ,-40 ,-40 ,0 ,-25 ,0 ,45 ,25 ,-20 ,90 ,25 ,0 ,0.7 ,0,0.5,0.2,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-30 ,-145 ,-155 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-60 ,90 ,35 ,0 ,0.7 ,0,0.5,0.2,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-30 ,-145 ,-155 ,-90 ,0 ,-90 ,0 ,90 ,90 ,-135 ,90 ,35 ,0 ,0.7 ,0,0.6,0.6,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-30 ,-95 ,-45 ,-50 ,0 ,-90 ,-5 ,85 ,65 ,-200 ,90 ,35 ,0 ,0.7 ,0,0.7,0.7,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-30 ,-95 ,-45 ,-50 ,0 ,-85 ,-5 ,35 ,30 ,-265 ,90 ,35 ,0 ,0.7 ,0,0.9,0.9,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,-35 ,0 ,0 ,-30 ,0 ,-40 ,10 ,0 ,-5 ,-5 ,0 ,0 ,-345 ,90 ,35 ,0.1 ,0.5 ,0,0.7,0.7,0.0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,90 ,0 ,0 ,0.5 ,0,0.6,0.6,0,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70} };

float frontFlipPoses[9][31] = { {0 ,0 ,25 ,0 ,0 ,25 ,0 ,0 ,-35 ,0 ,-35 ,0 ,45 ,45 ,10 ,90 ,0 ,-0.6 ,0.5 ,0 ,0 ,-0.9 ,-0.7 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{0 ,0 ,-75 ,0 ,0 ,-75 ,0 ,0 ,-25 ,0 ,-25 ,0 ,20 ,25 ,40 ,90 ,0 ,-0.3 ,0.7 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5},
{0 ,0 ,-170 ,0 ,0 ,-170 ,0 ,0 ,-60 ,0 ,-60 ,0 ,90 ,90 ,160 ,90 ,0 ,-0.3 ,1 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5},
{0 ,0 ,-170 ,0 ,0 ,-170 ,0 ,0 ,-60 ,0 ,-60 ,0 ,90 ,90 ,190 ,90 ,0 ,0.3 ,1 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5},
{0 ,0 ,-95 ,0 ,0 ,-95 ,0 ,0 ,-60 ,0 ,-60 ,0 ,90 ,90 ,275 ,90 ,0 ,0.3 ,0.8 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5},
{0 ,0 ,-30 ,0 ,0 ,-30 ,0 ,0 ,-90 ,0 ,-90 ,0 ,90 ,90 ,345 ,90 ,0 ,0.4 ,0.4 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5},
{0 ,0 ,25 ,0 ,0 ,25 ,0 ,0 ,-90 ,0 ,-90 ,0 ,90 ,90 ,380 ,90 ,0 ,0.4 ,0.4 ,0 ,0 ,-0.9 ,-0.7 ,5 ,5 ,-5 ,-5 ,5 ,5 ,-5 ,-5}, 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 0.7, 0.5, 0, 0, -0.9, -0.7, 0, 0, 0, 0, 0, 0, 0, 0},
{65 ,0 ,-75 ,-120 ,0 ,0 ,-105 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-5 ,0 ,0.7 ,0.5 ,0 ,0 ,-0.9 ,-0.7 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}};


float pushUpPoses[9][31] = { {0 ,0 ,-60 ,0 ,0 ,-60 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,45 ,90 ,0 ,-0.1 ,0.4 ,0 ,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {0 ,0 ,-65 ,0 ,0 ,-65 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,65 ,90 ,0 ,0 ,0.2 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {0 ,0 ,-5 ,0 ,0 ,0 ,-100 ,-105 ,0 ,0 ,0 ,0 ,0 ,0 ,80 ,90 ,0 ,0.1 ,0.1 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {0 ,0 ,-65 ,0 ,0 ,-65 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,65 ,90 ,0 ,0 ,0.2 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
    {0 ,0 ,-5 ,0 ,0 ,0 ,-100 ,-105 ,0 ,0 ,0 ,0 ,0 ,0 ,80 ,90 ,0 ,0.1 ,0.1 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
 {0 ,0 ,-25 ,0 ,0 ,-25 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,20 ,90 ,0 ,-0.1 ,0.6 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
 {55 ,75 ,0 ,-45 ,-80 ,0 ,-105 ,-100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0.5 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
 {55 ,-90 ,0 ,-50 ,90 ,0 ,-105 ,-100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0.5 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70},
       {55 ,-90 ,0 ,-50 ,90 ,0 ,-105 ,-100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0.5 ,0,0 ,-0.9 ,-0.7,-15 ,-70 ,5 ,70 ,-15 ,-70 ,5 ,70} };

// RGBA

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = { 0.5, 5.0, 0.0, 1.0 };
GLfloat lightPos1[] = { -0.5, -5.0, -2.0, 1.0 };
GLfloat lightPos2[] = { 0.0, 0.0, 2.0, 1.0 };

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
		0,							  //0 for now
		GL_RGB,					  //Format OpenGL uses for image
		image->width, image->height, //Width and height
		0,							  //The border of the image
		GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
									 //as unsigned numbers
		image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId2;
//Initializes 3D rendering
void initRendering()
{
	Image* image = loadBMP(floorTexture);
	_textureId = loadTexture(image);
    Image* image2 = loadBMP("images/wall.bmp");
    _textureId2 = loadTexture(image2);
	delete image;
    delete image2;
	// Turn on the power
	glEnable(GL_LIGHTING);
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
}
void drawmodel(char* filename)
{
    GLMmodel* model = glmReadOBJ(filename);
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);
    glmScale(model, .15);
    glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}

void newPoses(float pos[9][31],float newpos[9][31]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 23; j++) {
            pos[i][j] = newpos[i][j];
        }

    }


}

void screen_menu(int value)
{

    switch (value)
    {
    case '1':
       
        newPoses(poses, chillPos);
        break;
    case '2':
       
        newPoses(poses, backFlipPoses);
        break;
    case '3':
       
        newPoses(poses, pushUpPoses);
        break;

    case '4':

        newPoses(poses, frontFlipPoses);
        break;

    case '5':
        floorTexture = "images/wall.bmp";
        
        _textureId = loadTexture(loadBMP(floorTexture));
        break;

    case '6':
        floorTexture = "images/grass.bmp";
        
        _textureId = loadTexture(loadBMP(floorTexture));
        break;

    case '7':
        floorTexture = "images/wood.bmp";
   
        _textureId = loadTexture(loadBMP(floorTexture));
        break;

    }
    
    glutPostRedisplay();
}

void main_menu(int value) {
    if (value == 1)
    {
        cout << LeftShoulder_1 << " ,";
        cout << LeftShoulder_2 << " ,";
        cout << LeftShoulder_3 << " ,";
        cout <<  RightShoulder_1 << " ,";
        cout <<  RightShoulder_2 << " ,";
        cout <<  RightShoulder_3 << " ,";
        cout << LeftElbow << " ,";
        cout <<  RightElbow << " ,";
        cout << LeftPelv_1 << " ,";
        cout << LeftPelv_2 << " ,";
        cout <<  RightPelv_1 << " ,";
        cout <<  RightPelv_2 << " ,";
        cout << LeftKnee << " ,";
        cout << RightKnee << " ,";
        cout <<  bodyAngleX << " ,";
        cout <<  bodyAngleY << " ,";
        cout <<  bodyAngleZ << " ,";
        cout <<  bodyPos[0] << " ,";
        cout <<  bodyPos[1] << " ,";
        cout << bodyPos[2] << " ,";
        cout << modelpos[0] << " ,";
        cout << modelpos[1] << " ,";
        cout << modelpos[2] << " ,";
        cout << leftFingersBase << " ,";
        cout << leftFingersUp << " ,";
        cout << rightFingersBase << " ,";
        cout << rightFingersUp << " ,";
        cout << leftThmbBase << " ,";
        cout << leftThmbUp << " ,";
        cout << rightThmbBase << " ,";
        cout << rightThmbUp << endl;
    }
    else if (value == 2)
    {
        for (int i = 0; i < 3; i++) {
            cout << "eye " << i << eye[i] << " ,";
        }

    }

    

}

void setPoses(int frameNum) {
    LeftShoulder_1 = poses[frameNum][0];
    LeftShoulder_2 = poses[frameNum][1];
    LeftShoulder_3 = poses[frameNum][2];
    RightShoulder_1 = poses[frameNum][3];
    RightShoulder_2 = poses[frameNum][4];
    RightShoulder_3 = poses[frameNum][5];
    LeftElbow = poses[frameNum][6];
    RightElbow = poses[frameNum][7];
    LeftPelv_1 = poses[frameNum][8];
    LeftPelv_2 = poses[frameNum][9];
    RightPelv_1 = poses[frameNum][10];
    RightPelv_2 = poses[frameNum][11];
    LeftKnee = poses[frameNum][12];
    RightKnee = poses[frameNum][13];
    bodyAngleX = poses[frameNum][14];
    bodyAngleY = poses[frameNum][15];
    bodyAngleZ = poses[frameNum][16];
    bodyPos[0] = poses[frameNum][17];
    bodyPos[1] = poses[frameNum][18];
    bodyPos[2] = poses[frameNum][19];
    modelpos[0] = poses[frameNum][20];
    modelpos[1] = poses[frameNum][21];
    modelpos[2] = poses[frameNum][22];
    leftFingersBase = poses[frameNum][23];
    leftFingersUp = poses[frameNum][24];
    rightFingersBase = poses[frameNum][25];
    rightFingersUp = poses[frameNum][26];
    leftThmbBase = poses[frameNum][27];
    leftThmbUp = poses[frameNum][28];
    rightThmbBase = poses[frameNum][29];
    rightThmbUp = poses[frameNum][30];



}
void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void turnLeft()
{
	double theta = -PI / 100;
	rotatePoint(up, theta, eye);
}

void turnRight()
{
	double theta = PI / 100;
	rotatePoint(up, theta, eye);
}

void moveUp()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 100, eye);
	rotatePoint(horizontal, PI / 100, up);
}


void moveDown()
{

	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, -PI / 100, eye);
	rotatePoint(horizontal, -PI / 100, up);
}

void moveForward()
{

	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{

	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}



void display(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear Depth and Color buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 1);
	glTexCoord2f(3.0f, 0.0f); glVertex3f(1, -1, 1);
	glTexCoord2f(3.0f, 3.0f); glVertex3f(1, -1, -1);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-1, -1, -1);

	glEnd();
	glDisable(GL_TEXTURE_2D);
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 1);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(-1, 1, 1);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(-1, 1, -1);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(-1, -1, -1);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, 1);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(1, 1, 1);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(1, 1, -1);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(1, -1, -1);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, -1);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(-1, 1, -1);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(1, 1, -1);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(1, -1, -1);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 1, -1);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(1, 1, -1);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(1, 1, 1);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(-1, 1, 1);

   
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
 
    glTranslatef(-0.5 ,-0.6 ,-0.6);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(3,3,3);
    drawmodel((char*)modelname);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(modelpos[0],modelpos[1],modelpos[2]);
    glRotatef(ballAngle, 0.0, 0.0, 1.0);
    glScalef(1, 1, 1);
    drawmodel((char*)modelname2);
    glPopMatrix();

    glTranslatef(bodyPos[0], bodyPos[1], bodyPos[2]);
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(0.0, -3.6, 0.0);
    glRotatef(bodyAngleY, 0.0, 1.0, 0.0);
    glRotatef(bodyAngleX, 1.0, 0.0, 0.0);
    
   
    glTranslatef(0.0, 3.6, 0.0);
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidSphere(0.4, 20, 8);//draw head
    glPopMatrix();
    glTranslatef(0.0, -2.1, 0.0);
    glPushMatrix();
    glScalef(1.5, 3.0, 0.5);
    glutSolidCube(1.0); //draw body
    glPopMatrix();


    //Draw left arm
    glPushMatrix();
    glTranslatef(1.05, 1.3, 0.0);
    glRotatef((GLfloat)LeftShoulder_1, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)LeftShoulder_2, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)LeftShoulder_3, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.75, 0.0);
    
    glPushMatrix();
    glScalef(0.2, 1.5, 0.5);
    glutSolidCube(1.0); //shoulder
    glPopMatrix();
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef((GLfloat)LeftElbow, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.2, 1.5, 0.5);
    glutSolidCube(1.0);//elbow
    glPopMatrix();

    //draw fingers
    glPushMatrix();
    glTranslatef(0.06, -0.75, 0.21);
    glRotatef((GLfloat)leftFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.06, -0.75, 0.07);
    glRotatef((GLfloat)leftFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.06, -0.75, -0.07);
    glRotatef((GLfloat)leftFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06, -0.75, -0.21);
    glRotatef((GLfloat)leftFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.06, -0.75, 0.21);
    glRotatef((GLfloat)leftThmbBase, -2.5, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)leftThmbUp, -2.5, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();



    //Draw Right arm 
    glPushMatrix();
    glTranslatef(-1.05, 1.3, 0.0);
    glRotatef((GLfloat)RightShoulder_1, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)RightShoulder_2, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)RightShoulder_3, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.2, 1.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef((GLfloat)RightElbow, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.2, 1.5, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.06, -0.75, 0.21);
    glRotatef((GLfloat)rightFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.06, -0.75, 0.07);
    glRotatef((GLfloat)rightFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-0.06, -0.75, -0.07);
    glRotatef((GLfloat)rightFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.06, -0.75, -0.21);
    glRotatef((GLfloat)rightFingersBase, 0.0, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightFingersUp, 0.0, 0.0, 1.0); //finger flang 3
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06, -0.75, 0.21);
    glRotatef((GLfloat)rightThmbBase, 2.5, 0.0, 1.0);//finger flang 1
    glTranslatef(0.0, -0.1, 0.0);
    glPushMatrix();
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)rightThmbUp, 2.5, 0.0, 1.0); //finger flang 2
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.08, 0.2, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();


    //Draw Left leg
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glRotatef((GLfloat)LeftPelv_1, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)LeftPelv_2, 0.0, 0.0, 1.0);
    glTranslatef(0.45, -0.875, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.75, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.875, 0.0);
    glRotatef((GLfloat)LeftKnee, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.875, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.75, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -1.125, 0.25);
   
    glScalef(0.5, 0.5, 1.125);
    glutSolidCube(1.0);
    glPopMatrix();



    //Draw Right leg
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glRotatef((GLfloat)RightPelv_1, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)RightPelv_2, 0.0, 0.0, 1.0);
    glTranslatef(-0.45, -0.875, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.75, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -0.875, 0.0);
    glRotatef((GLfloat)RightKnee, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.875, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.75, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(0.0, -1.125, 0.25);
    glScalef(0.5, 0.5, 1.125);
    glutSolidCube(1.0);
    glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		turnLeft();
		break;
	case GLUT_KEY_RIGHT:
		turnRight();
		break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'n':
		moveForward();
		break;
	case 'b':
		moveBack();
		break;

    case '+':
        bodyAngleX = bodyAngleX + 5;
        break;

    case '-':
        bodyAngleX = bodyAngleX - 5;
        break;

    case '*':
        bodyAngleY = bodyAngleY + 5;
        break;

    case '/':
        bodyAngleY = bodyAngleY - 5;
        break;

    case '?':
        bodyAngleZ = bodyAngleZ + 5;
        break;

    case ':':
        bodyAngleZ = bodyAngleZ - 5;
        break;

    case '1':
        bodyPos[2] = bodyPos[2] - 0.1;
        break;
    case '5':
        bodyPos[2] = bodyPos[2] + 0.1;
        break;
    case '4':
        bodyPos[0] = bodyPos[0] - 0.1;
        break;
    case '6':
        bodyPos[0] = bodyPos[0] + 0.1;
        break;
    case '8':
        bodyPos[1] = bodyPos[1] + 0.1;
        break;
    case '2':
        bodyPos[1] = bodyPos[1] - 0.1;
        break;

    case 'k':
        modelpos[2] = modelpos[2] - 0.1;
        break;
    case 'K':
        modelpos[2] = modelpos[2] + 0.1;
        break;
    case 'h':
        modelpos[0] = modelpos[0] - 0.1;
        break;
    case 'H':
        modelpos[0] = modelpos[0] + 0.1;
        break;
    case 'J':
        modelpos[1] = modelpos[1] + 0.1;
        break;
    case 'j':
        modelpos[1] = modelpos[1] - 0.1;
        break;
    case 'q':
        if (LeftShoulder_1 >= 190) { break; }
        else
        {
            LeftShoulder_1 = (LeftShoulder_1 + 5);

            break;
        }
    case 'Q':
        if (LeftShoulder_1 <= 0) { break; }
        else {
            LeftShoulder_1 = (LeftShoulder_1 - 5);
            glutPostRedisplay();
            break;
        }

    case 'a':
        if (LeftShoulder_2 >= 90) { break; }
        else
        {
            LeftShoulder_2 = (LeftShoulder_2 + 5);

            break;
        }
    case 'A':
        if (LeftShoulder_2 <= -90) { break; }
        else {
            LeftShoulder_2 = (LeftShoulder_2 - 5);
            glutPostRedisplay();
            break;
        }

    case '7':
        if (LeftShoulder_3 <= -170) { break; }
        else
        {
            LeftShoulder_3 = (LeftShoulder_3 - 5);

            break;
        }
    case '!':
        if (LeftShoulder_3 >= 90) { break; }
        else {
            LeftShoulder_3 = (LeftShoulder_3 + 5);
            glutPostRedisplay();
            break;
        }


    case 'r':
        if (RightShoulder_1 <= -190) { break; }
        else
        {
            RightShoulder_1 = (RightShoulder_1 - 5);

            break;
        }
    case 'R':
        if (RightShoulder_1 >= 0) { break; }
        else {
            RightShoulder_1 = (RightShoulder_1 + 5);
            glutPostRedisplay();
            break;
        }

    case 'f':
        if (RightShoulder_2 <= -90) { break; }
        else
        {
            RightShoulder_2 = (RightShoulder_2 - 5);

            break;
        }
    case 'F':
        if (RightShoulder_2 >= 90) { break; }
        else {
            RightShoulder_2 = (RightShoulder_2 + 5);
            glutPostRedisplay();
            break;
        }

    case '9':
        if (RightShoulder_3 <= -170) { break; }
        else
        {
            RightShoulder_3 = (RightShoulder_3 - 5);

            break;
        }
    case '@':
        if (RightShoulder_3 >= 90) { break; }
        else {
            RightShoulder_3 = (RightShoulder_3 + 5);
            glutPostRedisplay();
            break;
        }


    case 'z':
        if (LeftElbow <= -170) { break; }
        else
        {
            LeftElbow = (LeftElbow - 5);

            break;
        }
    case 'Z':
        if (LeftElbow >= 0) { break; }
        else {
            LeftElbow = (LeftElbow + 5);
            glutPostRedisplay();
            break;
        }

    case 'v':
        if (RightElbow <= -170) { break; }
        else
        {
            RightElbow = (RightElbow - 5);

            break;
        }
    case 'V':
        if (RightElbow >= 0) { break; }
        else {
            RightElbow = (RightElbow + 5);
            glutPostRedisplay();
            break;
        }

    case 'w':
        if (LeftPelv_1 <= -90) { break; }
        else
        {
            LeftPelv_1 = (LeftPelv_1 - 5);

            break;
        }
    case 'W':
        if (LeftPelv_1 >= 50) { break; }
        else {
            LeftPelv_1 = (LeftPelv_1 + 5);
            glutPostRedisplay();
            break;
        }

    case 's':
        if (LeftPelv_2 >= 90) { break; }
        else
        {
            LeftPelv_2 = (LeftPelv_2 + 5);

            break;
        }
    case 'S':
        if (LeftPelv_2 <= -10) { break; }
        else {
            LeftPelv_2 = (LeftPelv_2 - 5);
            glutPostRedisplay();
            break;
        }

    case 'e':
        if (RightPelv_1 <= -90) { break; }
        else
        {
            RightPelv_1 = (RightPelv_1 - 5);

            break;
        }
    case 'E':
        if (RightPelv_1 >= 50) { break; }
        else {
            RightPelv_1 = (RightPelv_1 + 5);
            glutPostRedisplay();
            break;
        }

    case 'd':
        if (RightPelv_2 <= -90) { break; }
        else
        {
            RightPelv_2 = (RightPelv_2 - 5);

            break;
        }
    case 'D':
        if (RightPelv_2 >= 10) { break; }
        else {
            RightPelv_2 = (RightPelv_2 + 5);
            glutPostRedisplay();
            break;
        }

    case 'x':
        if (LeftKnee >= 90) { break; }
        else
        {
            LeftKnee = (LeftKnee + 5);

            break;
        }
    case 'X':
        if (LeftKnee <= 0) { break; }
        else {
            LeftKnee = (LeftKnee - 5);
            glutPostRedisplay();
            break;
        }

    case 'c':
        if (RightKnee >= 90) { break; }
        else
        {
            RightKnee = (RightKnee + 5);

            break;
        }
    case 'C':
        if (RightKnee <= 0) { break; }
        else {
            RightKnee = (RightKnee - 5);
            glutPostRedisplay();
            break;
        }

    case 'u':
        if (leftFingersBase >= 5) {

            if (leftFingersUp >= 5) { break; }
            else {
                leftThmbUp = (leftThmbUp + 5);
                leftFingersUp = (leftFingersUp + 5);

                glutPostRedisplay();
                break;
            }

        }
        else {
            leftThmbBase = (leftThmbBase + 5);
            leftFingersBase = (leftFingersBase + 5);
            glutPostRedisplay();
            break;
        }

    case 'U':
        if (leftFingersBase <= -40) {
            if (leftFingersUp <= -70) { break; }
            else {
                leftThmbUp = (leftThmbUp - 5);
                leftFingersUp = (leftFingersUp - 5);

                glutPostRedisplay();
                break;
            }
        }
        else {
            leftThmbBase = (leftThmbBase - 5);
            leftFingersBase = (leftFingersBase - 5);
            glutPostRedisplay();
            break;
        }

    case 'y':
        if (rightFingersBase <= -5) {

            if (rightFingersUp <= -5) { break; }
            else {
                rightThmbUp = (rightThmbUp - 5);
                rightFingersUp = (rightFingersUp - 5);

                glutPostRedisplay();
                break;
            }

        }
        else {
            rightThmbBase = (rightThmbBase - 5);
            rightFingersBase = (rightFingersBase - 5);
            glutPostRedisplay();
            break;
        }

    case 'Y':
        if (rightFingersBase >= 40) {
            if (rightFingersUp >= 70) { break; }
            else {
                rightThmbUp = (rightThmbUp + 5);
                rightFingersUp = (rightFingersUp + 5);

                glutPostRedisplay();
                break;
            }
        }
        else {
            rightThmbBase = (rightThmbBase + 5);
            rightFingersBase = (rightFingersBase + 5);
            glutPostRedisplay();
            break;
        }

    

	case 27:
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void attachMenu()
{
    glutCreateMenu(screen_menu);
    glutAddMenuEntry("Movments and floorTexture", 0);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("Chill pos ", '1');
    glutAddMenuEntry("Back flip", '2');
    glutAddMenuEntry("Front flip", '4');
    glutAddMenuEntry("Push up", '3');
    glutAddMenuEntry("wall", '5');
    glutAddMenuEntry("grass", '6');
    glutAddMenuEntry("wood", '7');
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutCreateMenu(main_menu);
    glutAddMenuEntry("Capture Pose", 1);
    glutAddMenuEntry("Eye", 2);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

static int f = 0;
void timer(int value) {
    f = f % 9;
    setPoses(f);
    f++;
    glutPostRedisplay();
    glutTimerFunc(500,timer,0);

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Task 3");
    attachMenu();
   
	initRendering();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.1, 10);
    glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
