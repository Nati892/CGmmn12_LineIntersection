#include "Scene.h"
#define PI 3.14159265f
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "Beautiful Lines"

int scale_x_start = -960;
int scale_x_end = 960;
int scale_y_start = -540;
int scale_y_end = 540;

int scale_y = 0;
int scale_x = 800;
int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 1920;
int CurrentSceneHeight = 1080;

int InputXtranslation = 0;
int InputYtranslation = 0;
int InputRotationAngle = 0;
std::vector<Point2Dd*> LineDrawPointsVec;
//Draws the background: grass and sky
void DrawBackgound()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(scale_x_start, scale_y_start, scale_x_end, scale_y_end);
	glColor3f(0.0f, 0.0f, 0.0f);

	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glVertex2f(scale_x_start, 0.0f);
	glVertex2f(scale_x_end, 0.0f);
	glVertex2f(0.0f, scale_y_start);
	glVertex2f(0.0f, scale_y_end);

	glEnd();

}

bool onSegment(Point2Dd p, Point2Dd q, Point2Dd r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

int Orientation(Point2Dd p, Point2Dd q, Point2Dd r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

//used to check if lines intersect at all
bool CheckIfLinesIntersect(Point2Dd p1, Point2Dd q1, Point2Dd p2, Point2Dd q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, q2);
	int o3 = Orientation(p2, q2, p1);
	int o4 = Orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

//if lines intersect it returns the point
Point2Dd* GetIntersectionPoint(Point2Dd p1, Point2Dd q1, Point2Dd p2, Point2Dd q2) {
	// Calculate line equations for each line segment
	Line line1, line2;

	if (p1.x == q1.x) {
		// Vertical line
		line1.slope = std::numeric_limits<double>::infinity();
		line1.intercept = p1.x;
	}
	else {
		line1.slope = static_cast<double>(q1.y - p1.y) / (q1.x - p1.x);
		line1.intercept = p1.y - line1.slope * p1.x;
	}

	if (p2.x == q2.x) {
		// Vertical line
		line2.slope = std::numeric_limits<double>::infinity();
		line2.intercept = p2.x;
	}
	else {
		line2.slope = static_cast<double>(q2.y - p2.y) / (q2.x - p2.x);
		line2.intercept = p2.y - line2.slope * p2.x;
	}

	// Check if the lines are parallel
	if (line1.slope == line2.slope) {
		std::cout << "Lines are parallel. No intersection point exists." << std::endl;
		return nullptr;
	}

	// Calculate intersection point
	Point2Dd* intersectionPoint = new Point2Dd();
	intersectionPoint->x = (line2.intercept - line1.intercept) / (line1.slope - line2.slope);
	intersectionPoint->y = line1.slope * intersectionPoint->x + line1.intercept;

	return intersectionPoint;
}

/// <summary>
/// 
/// </summary>
/// <param name="eq_a">the 'a' parameter of the ax^2+b parabula,assuming this isnt 0</param>
/// <param name="eq_b">the 'b' parameter of the ax^2+b parabula</param>
/// <param name="x_range">range for the positive x and also symetricly for negatives</param>
void DrawLines(Point2Dd p1, Point2Dd q1, Point2Dd p2, Point2Dd q2, bool FirstLineOnly = false)
{
	Point2Dd* intersection_point = nullptr;
	bool DoLinesIntersect = false;
	if (!FirstLineOnly)
	{
		DoLinesIntersect = CheckIfLinesIntersect(p1, q1, p2, q2);
		if (DoLinesIntersect)
			intersection_point = GetIntersectionPoint(p1, q1, p2, q2);

	}
	glLineWidth(3.0f);
	glBegin(GL_LINES);

	//draw first line in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(p1.x, p1.y);
	glVertex2i(q1.x, q1.y);
	glEnd();

	if (!FirstLineOnly)
	{
		//draw second line in blue
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(p2.x, p2.y);
		glVertex2i(q2.x, q2.y);
		glEnd();
	}

	if (DoLinesIntersect && intersection_point != nullptr)//draw intersection point in green
	{
		glPointSize(7.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2d(intersection_point->x, intersection_point->y);
		delete intersection_point;
		glEnd();
	}

}

void DrawSingleLine(Point2Dd p1, Point2Dd q1)
{
	DrawLines(p1, q1, Point2Dd(), Point2Dd(), true);
}

void CleanupAndExit()
{
	exit(0);
}

//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;
	glViewport(StartPos_X, StartPos_Y, finalW, finalH);
}

//Redraw callback
void DisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	FixAspectRatio();

	DrawBackgound();

	glTranslatef(InputXtranslation, InputYtranslation,0.0);
	glRotatef(InputRotationAngle,0.0,0.0,1.0);

	Point2Dd* p1 = nullptr;
	Point2Dd* q1 = nullptr;
	Point2Dd* p2 = nullptr;
	Point2Dd* q2 = nullptr;
	for (auto i = LineDrawPointsVec.begin(); i != LineDrawPointsVec.end(); ++i)
	{
		if (p1 == nullptr)
		{
			p1 = *i;
			continue;
		}

		if (q1 == nullptr)
		{
			q1 = *i;
			continue;
		}
		if (p2 == nullptr)
		{
			p2 = *i;
			continue;
		}
		if (q2 == nullptr)
		{
			q2 = *i;
			DrawLines(*p1, *q1, *p2, *q2);

			//clear em'
			p1 = nullptr;
			q1 = nullptr;
			p2 = nullptr;
			q2 = nullptr;
			continue;
		}
		//case all are full
	}
	if (q1 != nullptr)
	{
		DrawSingleLine(*p1, *q1);
	}


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(scale_x_start, scale_x_end, scale_y_start, scale_y_end);

	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;
	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;

	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);

	//convert to rect coordinates
	float rectx = scale_x_start + (std::abs(scale_x_end - scale_x_start) * converted_x);
	float recty = scale_y_start + (std::abs(scale_y_end - scale_y_start) * converted_y);
	Point2Dd* tmp = new Point2Dd(rectx, recty);
	LineDrawPointsVec.push_back(tmp);
	glutPostRedisplay();
	//Add point to list

}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'd':
	case 'D':
		InputXtranslation++;
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':
		InputXtranslation--;
		glutPostRedisplay();
		break;

	case 'w':
	case 'W':
		InputYtranslation++;
		glutPostRedisplay();
		break;

	case 's':
	case 'S':
		InputYtranslation--;
		glutPostRedisplay();
		break;

	case '1':
		InputRotationAngle++;
		glutPostRedisplay();
		break;

	case '2':
		InputRotationAngle--;
		glutPostRedisplay();
		break;


	case 'q':
	case 'Q':
		exit(0);
	}
}

//my initiation function
void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1920;
	CurrentSceneHeight = 1080;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth;
	AspectRatioDenominator = CurrentSceneHeight;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(MY_HEADER);
	LoadBasePoints();


}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);
	glutKeyboardFunc(KeyboardEventCallback);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{
	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();

}


void LoadBasePoints()
{
	//Line pair 1
	Point2Dd* p1 = new Point2Dd(0, 0);
	Point2Dd* q1 = new Point2Dd(200, 200);
	Point2Dd* p2 = new Point2Dd(200, 0);
	Point2Dd* q2 = new Point2Dd(0, 200);

	LineDrawPointsVec.push_back(p1);
	LineDrawPointsVec.push_back(q1);
	LineDrawPointsVec.push_back(p2);
	LineDrawPointsVec.push_back(q2);

	//DrawLines(p1, q1, p2, q2);

	//Line pair 2
	p1 = new Point2Dd(0, 0);
	q1 = new Point2Dd(-200, 10);
	p2 = new Point2Dd(-20, 10);
	q2 = new Point2Dd(-40, -30);

	LineDrawPointsVec.push_back(p1);
	LineDrawPointsVec.push_back(q1);
	LineDrawPointsVec.push_back(p2);
	LineDrawPointsVec.push_back(q2);

	//Line pair 3
	p1 = new Point2Dd(30, -30);
	q1 = new Point2Dd(60, -40);
	p2 = new Point2Dd(30, -45);
	q2 = new Point2Dd(70, -50);

	LineDrawPointsVec.push_back(p1);
	LineDrawPointsVec.push_back(q1);
	LineDrawPointsVec.push_back(p2);
	LineDrawPointsVec.push_back(q2);
	//Line pair 4
	p1 = new Point2Dd(100, -30);
	q1 = new Point2Dd(160, -40);
	p2 = new Point2Dd(105, -25);
	q2 = new Point2Dd(170, -150);

	LineDrawPointsVec.push_back(p1);
	LineDrawPointsVec.push_back(q1);
	LineDrawPointsVec.push_back(p2);
	LineDrawPointsVec.push_back(q2);



}