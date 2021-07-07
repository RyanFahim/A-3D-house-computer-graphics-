#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawAxes = true;
float tyreAngle = 85;

float quadAngle = 0;
float boxAngle = 0;
float boxScaleFactor = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;
float movecar = 0;
Point pos, u, r, l;
float doorOpen = 0;
float doorClose= 0;

float boxAngleC = 0;
float boxAngleAC = 0;
float ghorbariSacleFactorX =1;
float ghorbariSacleFactorY =1;
float ghorbariSacleFactorZ =1;

float windowOpen =0;
float backDoorOpen = 0;


float slidingWindowUp =0;
float slidingWindowDown =0;

float tyreRotate = 0;

float rotationController = 0;

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 500,0,0); // a point on pos x axis
			glVertex3f(-500,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-500,0); // a point on pos y axis
			glVertex3f(0, 500,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 500);  // a point on pos z axis
			glVertex3f(0,0,-500);   // a point on neg z axis
		}
		glEnd();
	}
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

Point Cameraposition(Point vect, Point perp, int dir)
{
    double s = dir * 3.0;

    Point point;
    point.x =  vect.x + s * perp.x;  /// pos->x + (-1/1) * (l/r/u)->x
    point.y =  vect.y + s * perp.y; /// pos->y + (-1/1) * (l/r/u)->y
    point.z =  vect.z + s * perp.z; /// pos->y + (-1/1) * (l/r/u)->z
    return point;
}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}

		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }
        case '7':{


            tyreScaleFactor += 0.2;
            break;
//            tyreScaleFactor += 0.2;
//            break;
        }



        case '9':{
            if(windowOpen == -70){
                break;

            }
            else{
                windowOpen-=5;
            }

            break;
        }

        case '0':{
            if(windowOpen == 0){
                break;

            }
            else{
                windowOpen+=5;
            }

            break;
        }


        case 'l':{
            boxAngleC -= 5;
            break;
        }

        case 'L':{
            boxAngleC -= 5;
            break;
        }

        case 'r':{
            boxAngleC += 5;
            break;
        }

        case 'R':{
            boxAngleC += 5;
            break;
        }
        case 'u':{

            if(ghorbariSacleFactorX<= 1.120000 && ghorbariSacleFactorY<= 1.120000 && ghorbariSacleFactorZ<= 1.120000)
            {
                ghorbariSacleFactorX +=0.015;
                ghorbariSacleFactorY +=0.015;
                ghorbariSacleFactorZ +=0.015;
            }
            break;

        }

        case 'U':{

            if(ghorbariSacleFactorX<= 1.120000 && ghorbariSacleFactorY<= 1.120000 && ghorbariSacleFactorZ<= 1.120000)
            {
                ghorbariSacleFactorX +=0.015;
                ghorbariSacleFactorY +=0.015;
                ghorbariSacleFactorZ +=0.015;
            }
            break;

        }

        case 'd':{

            if(ghorbariSacleFactorX>= 0.010001 && ghorbariSacleFactorY>= 0.010001 && ghorbariSacleFactorZ>= 0.010001)
            {
                ghorbariSacleFactorX -=0.015;
                ghorbariSacleFactorY -=0.015;
                ghorbariSacleFactorZ -=0.015;
            }

            break;
    }

      case 'D':{

            if(ghorbariSacleFactorX>= 0.010001 && ghorbariSacleFactorY>= 0.010001 && ghorbariSacleFactorZ>= 0.010001)
            {
                ghorbariSacleFactorX -=0.015;
                ghorbariSacleFactorY -=0.015;
                ghorbariSacleFactorZ -=0.015;
            }

            break;
    }




		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
		        point pos1 = Cameraposition(pos, l, -1);
                pos = pos1;
                break;
//		        quadAngle += 5;
//		        printf("Quad Angle %f\n", quadAngle);
//		        break;
		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        point pos1 = Cameraposition(pos, l, 1);
                pos = pos1;
                break;

//		        quadAngle -= 5;
//		        printf("Quad Angle %f\n", quadAngle);
//		        break;
		    }

		case GLUT_KEY_RIGHT:    // right arrow
		    {

		         point pos1 = Cameraposition(pos, r, 1);
                pos = pos1;
                break;

//		        boxAngle += 5;
//		        printf("Box Angle %f\n", boxAngle);
//		        break;
		    }

		case GLUT_KEY_LEFT:     // left arrow
		    {
                point pos1 = Cameraposition(pos, r, -1);
                pos = pos1;
                break;
//		        boxAngle -= 5;
//		        printf("Box Angle %f\n", boxAngle);
//		        break;
		    }

		case GLUT_KEY_PAGE_UP:
		    {
		        point pos1 = Cameraposition(pos, u, 1);
                pos = pos1;
                break;
//                boxScaleFactor += 0.2;
//                break;
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        point pos1 = Cameraposition(pos, u, -1);
                pos = pos1;
                break;
//		        boxScaleFactor -= 0.2;
//                break;
		    }

		case GLUT_KEY_HOME:
		    {

                if(doorOpen == 20){

                    break;

                }
		        else{
                    doorOpen +=5;
                    doorClose -= 5;
		        }
		        break;


		    }

        case GLUT_KEY_END:
            {
                 if(doorClose == 0){

                    break;
                }
		        else{
                    doorClose +=5;
                    doorOpen -= 5;
		        }
		        break;
            }

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {
                printf("Mouse Left Button Clicked\n");
			}
			else if(state == GLUT_UP)
            {
                printf("Mouse Left Button Released\n");
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2, halfSqureWidth = tyreWidth/2;

    for(int j=1; j<=7; j++){
    glPushMatrix();


    glRotatef(100*j, 1,0,0);
    glBegin(GL_QUADS);

    {
        if(j%2 == 0){
            glColor3f(0.8, 0.5, 1);
            glVertex3f(halfSqureWidth, tyreRadius, 0);
            glVertex3f(-halfSqureWidth, tyreRadius, 0);
            glVertex3f(-halfSqureWidth, -tyreRadius, 0);
            glVertex3f(halfSqureWidth, -tyreRadius, 0);
        }

        else{
            glColor3f(0, 0.8, 0.2);
            glVertex3f(halfSqureWidth, tyreRadius, 0);
            glVertex3f(-halfSqureWidth, tyreRadius, 0);
            glVertex3f(-halfSqureWidth, -tyreRadius, 0);
            glVertex3f(halfSqureWidth, -tyreRadius, 0);
        }

    }
    glEnd();
    glPopMatrix();
    }



    glPushMatrix();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
    }
    glEnd();

// glColor3f(0.25, 0.5, 1);
    for(int i=0; i<tyreSlices; i++)
    {
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            if(i%2 == 0){
            glColor3f(1,1,1);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);

            }

            else{
                glColor3f(0,0,0);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

        }
        glEnd();
        glPopMatrix();
    }
}




void displayTyre2(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

//    glColor3f(1, 0, 0);
//    glBegin(GL_QUADS);
//    {
//        glVertex3f(halfTyreWidth, tyreRadius, 0);
//        glVertex3f(-halfTyreWidth, tyreRadius, 0);
//        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
//        glVertex3f(halfTyreWidth, -tyreRadius, 0);
//    }
//    glEnd();
//
//    glColor3f(1, 0, 0);
//    glBegin(GL_QUADS);
//    {
//        glVertex3f(halfTyreWidth, 0, tyreRadius);
//        glVertex3f(halfTyreWidth, 0, -tyreRadius);
//        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
//        glVertex3f(-halfTyreWidth, 0, tyreRadius);
//    }
//    glEnd();


    glColor3f(0.25, 0.5, 1);
    for(int i=0; i<tyreSlices; i++)
    {
         glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            if(i%2 == 0){
            glColor3f(1,1,1);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);

            }

            else{
            glColor3f(0,0,0);
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
            }

        }
        glEnd();
        glPopMatrix();
}

}
void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        //glColor3f(1, 1, 0);

        //glVertex3f(halfQuadWidth, 0, halfQuadLength);
        //glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, halfQuadLength);

        /** Gradient Fill Quad **/


        glColor3f(1, 1, 0);

        glVertex3f( 0, halfQuadWidth, halfQuadLength);
        glVertex3f(0, -halfQuadWidth, halfQuadLength);


//        glVertex3f(halfQuadWidth, 0, halfQuadLength);
//        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);

        glVertex3f(0, -halfQuadWidth,  -halfQuadLength);
        glVertex3f(0, halfQuadWidth, -halfQuadLength);

    }
    glEnd();
}


void displayWindowQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {

        /** Gradient Fill Quad **/

        glColor3f(1, 1, 0);
        glVertex3f( 0, quadWidth, 0);
        glVertex3f(0, quadWidth,  -quadLength);
        glVertex3f(0, -quadWidth, -quadLength);
        glVertex3f( 0, -quadWidth, 0);

;

    }
    glEnd();
}


void displayBackDoor1Quad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {


        glColor3f(0, 1, 0);
        glVertex3f( 0,  0, quadLength);
        glVertex3f( 0, 0, 0);

        glColor3f(1, 1, 1);
        glVertex3f( -quadWidth, 0, 0);
        glVertex3f(  -quadWidth, 0, quadLength);

;

    }
    glEnd();
}

void displayBackDoor2Quad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {

        /** Gradient Fill Quad **/

        glColor3f(0, 1, 0);
        glVertex3f( 0,  0, quadLength);
        glVertex3f( 0, 0, 0);

        glColor3f(1, 1, 1);
        glVertex3f( quadWidth, 0, 0);
        glVertex3f(  quadWidth, 0, quadLength);



;

    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayUpperBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.8, 0.8, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.8, 0.7, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.8, 0.5, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayRooftopBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.72, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 0.5, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0.6, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}




void displayHouseBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1,0,0);
//        glColor3f(0.788, 0.141, 0.0.549)

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.5,0,0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1,0,0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayBaseBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.23, 0.094, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.23, 0.094, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.01, 0.0705, 0.411);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayWindowBaseBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.23, 0.094, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


//        glColor3f(1, 1, 0);
       glColor3f(0.23, 0.094, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.01, 0.0705, 0.411);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayRoof(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayDoorLeft(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.55, 0.54, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.45, 0.44, 0.46);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.35, 0.34, 0.36);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayDoorRight(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.55, 0.54, 0.56);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.45, 0.44, 0.46);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.35, 0.34, 0.36);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayS1(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.25, 0.96, 0.30);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.15, 0.86, 0.20);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.05, 0.76, 0.10);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayS2(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 0, 0.3);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayS3(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.086,0.67,0.85);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
       glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.07,0.50,0.75);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.06,0.40,0.65);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 100, quadWidth = 50;
    float largeBoxLength = 500, largeBoxWidth = 300, largeBoxHeight = 30;
    float roofBoxLength = 500, roofBoxWidth = 300, roofBoxHeight = 20;
    float upperBoxLength = 250, upperBoxWidth = 80, upperBoxHeight = 250;
    float smallBoxLength = 480, smallBoxWidth = 280, smallBoxHeight = 150;
    float RoofLength = 375, RoofWidth = 50, RoofHeight = 80;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;

    float tyreRadius = 50, tyreWidth = 30;
    float tyreRadius2 = 30, tyreWidth2 = 30;

    float leftdoorBoxLength = 75, leftdoorBoxWidth = 30, leftdoorBoxHeight = 100;
    float rightdoorBoxLength = 75, rightdoorBoxWidth = 30, rightdoorBoxHeight = 100;

    float Stair1Length = 200, Stair1Width = 180, Stair1Height = 5;
    float Stair2Length = 170, Stair2Width = 150, Stair2Height = 5;
    float Stair3Length = 140, Stair3Width = 120, Stair3Height = 5;

    float quadLengthWindow = 70, quadWidthWindow = 50;


    /** Principal Axes **/



    /**/

    /** Quad **/
//
//    glRotatef(quadAngle, 1, 0, 0); // rotates with respect to x axis
//    glRotatef(quadAngle, 0, 1, 0); // rotates with respect to y axis
//    glRotatef(quadAngle, 0, 0, 1); // rotates with respect to z axis
    //glRotatef(windowOpen, 1,0,0);

//    displayBackDoor1Quad(quadLength, quadWidth);


    /**/

    /** Single Box **/

    //glTranslatef(150, 0, 0); // rotation applied first, translation applied second
    //glRotatef(boxAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(boxAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    //glTranslatef(150, 0, 0);    // translation applied first, rotation applied second
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight);

    /**/

    /** Double Box Stack **/

    //glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes
    //glTranslatef(-300, 100, 100); // translation applied to both boxes
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glRotatef(boxAngle, 0, 0, 1);   // rotation applied only on the small box
    //glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    //displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box

    /**/

    /** Double Box Stack - Push Pop Matrix **/


    /*glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes

    //glPushMatrix(); // saves the matrix just before scaling, to prevent scale effect to anything other than the large box
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor); // without push-pop, scale will be applied to both boxes
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glPopMatrix();

    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    */


    /**/

    /** Tyre **/

    /*
    */
    /**/

    /** Tyre Double Box Stack **/

    /*glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth);
    glPopMatrix();
    */
//glRotatef(quadAngle, 0, 0, 1);
 //glRotatef(boxAngle, 0, 0, 1);
    /** Animate Function **/

    glRotatef(boxAngleC, 0, 0, 1);
    glRotatef(boxAngleAC, 0, 0, 1);
    glScalef( ghorbariSacleFactorX, ghorbariSacleFactorY, ghorbariSacleFactorZ );

    displayAxes();

    ///Base
    glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBaseBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();


    ///Backdoor1
    glPushMatrix();
    glTranslatef( 50 , -(smallBoxWidth)/2 -2 ,largeBoxHeight -10);
    glRotatef(backDoorOpen, 0, 0, 1);
    displayBackDoor1Quad(quadLength, quadWidth);
    glPopMatrix();

    ///Backdoor2
    glPushMatrix();
    glTranslatef( -50 , -(smallBoxWidth)/2 -2 , largeBoxHeight -10);
    glRotatef(-backDoorOpen, 0, 0, 1);
    displayBackDoor2Quad(quadLength, quadWidth);
    glPopMatrix();


    ///window
    glPushMatrix();
    glTranslatef(largeBoxWidth - 55, 0 , 50);
    glTranslatef(0,0,80);
    glRotatef(windowOpen, 0, 1, 0);
    displayWindowQuad(quadLengthWindow, quadWidthWindow);
    glPopMatrix();

    ///window other side
    glPushMatrix();
    glTranslatef(-largeBoxWidth + 60, 0 , 80);
    glTranslatef(0,0, 0+ slidingWindowUp);
    displayWindowBaseBox(2, 70, 100); // large box
    glPopMatrix();



    ///House Body
    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayHouseBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();

    ///Roof top
    glPushMatrix();
    glTranslatef(0, 0, (roofBoxHeight/2) + (smallBoxHeight));
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayRooftopBox(roofBoxLength, roofBoxWidth, roofBoxHeight); // large box
    glPopMatrix();

    ///stair1
    glPushMatrix();
    glTranslatef(0,(largeBoxWidth/2), -10);
    displayS1(Stair1Length, Stair1Width, Stair1Height);
    glPopMatrix();

    ///stair2
    glPushMatrix();
    glTranslatef(0,(largeBoxWidth/2),Stair1Height -10);
    displayS2(Stair2Length, Stair2Width, Stair2Height);
    glPopMatrix();

    ///stair3
    glPushMatrix();
    glTranslatef(0,(largeBoxWidth/2),Stair1Height + Stair2Height -10);
    displayS3(Stair3Length, Stair3Width, Stair3Height);
    glPopMatrix();




    ///upper roof
    glPushMatrix();
    glTranslatef(0, 0,(smallBoxHeight) + roofBoxHeight);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayUpperBox(upperBoxLength, upperBoxWidth, upperBoxHeight); // large box
    glPopMatrix();

    ///front door left
    glPushMatrix();
    glTranslatef(40 + doorOpen - doorClose, (smallBoxWidth)/2 - 10 , (largeBoxHeight/2 + leftdoorBoxHeight/2) );
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayDoorLeft(leftdoorBoxLength, leftdoorBoxWidth, leftdoorBoxHeight); // large box
    glPopMatrix();

    ///front door right
    glPushMatrix();
    glTranslatef( -40 - doorOpen + doorClose, (smallBoxWidth)/2-10 , (largeBoxHeight/2 + rightdoorBoxHeight/2) );
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayDoorRight(rightdoorBoxLength, rightdoorBoxWidth, rightdoorBoxHeight); // large box
    glPopMatrix();






    ///tyre
    glPushMatrix();
    glTranslatef(0, upperBoxWidth-10 ,tyreRadius+smallBoxHeight+(largeBoxHeight/2)+roofBoxHeight); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 0, 1);// check what happens to the tyre after exchanging the order of translation and roatio
    glRotatef(tyreRotate , 1, 0 , 0);
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();


    ///smallTyre
    glPushMatrix();
    glTranslatef(0, upperBoxWidth-10 ,tyreRadius+smallBoxHeight+(largeBoxHeight/2)+roofBoxHeight); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    glRotatef(tyreRotate , 1, 0 , 0);
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre2(tyreRadius2, tyreWidth2); // tyre
    glPopMatrix();



}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(background, background, background,0);	//sets background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

	glutSwapBuffers();
}



void animate(){

    if(rotationController == 1){
        tyreRotate += 1;
    }

    else if(rotationController == 2){
        tyreRotate -= 1;
    }
     else if(rotationController == 3){
        tyreRotate == 0 ;
    }



	glutPostRedisplay();
}

void init(){
    glClearColor(background, background, background,0); 	//sets background color

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

	// to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 3)
    {
        background = 1;
    }
    else if(id == 4)
    {
        background = 0;
    }
}


void subMenuCircle(int id)
{
    if(id == 5)
    {

        rotationController = 1;



    }
    else if(id == 6)
    {

        rotationController = 2;
    }

    else{
        rotationController = 3;
    }
}



void subMenuWindow(int id)
{
    if(id == 7 && slidingWindowUp<20){

            slidingWindowUp += 20;
        }


    else if(id == 8  && slidingWindowUp> 0 ){
            slidingWindowUp -= 20;
        }



}


void subMenuDoor(int id)
{
    if(id == 9 && backDoorOpen<120)
    {

         backDoorOpen += 120;

    }
    else if(id == 10 && backDoorOpen> 0 )
    {
         backDoorOpen -= 120;
    }
}


void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("White", 3);
	glutAddMenuEntry("Black", 4);

	int subMenuCircleNo = glutCreateMenu(subMenuCircle);
	glutAddMenuEntry("Cloclwise", 5);
	glutAddMenuEntry("Anti Clockwise", 6);
	glutAddMenuEntry("Stop", 11);

	int subMenuWindowNo= glutCreateMenu(subMenuWindow);
	glutAddMenuEntry("Up", 7);
	glutAddMenuEntry("Down", 8);



	int subMenuDoorNo= glutCreateMenu(subMenuDoor);
	glutAddMenuEntry("Door open", 9);
	glutAddMenuEntry("Door Close", 10);


    glutCreateMenu(mainMenu);
	glutAddMenuEntry("Axes On", 1);
	glutAddMenuEntry("Axes Off", 2);
	glutAddSubMenu("Background", subMenuNo);


	glutAddSubMenu("Circle rotation", subMenuCircleNo);
	glutAddSubMenu("Sliding Window", subMenuWindowNo);
	glutAddSubMenu("Sliding Door", subMenuDoorNo);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
