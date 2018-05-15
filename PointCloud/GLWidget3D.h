#pragma once

#include <glew.h>
#include "Shader.h"
#include <QGLWidget>
#include <QMouseEvent>
#include "Camera.h"
#include "RenderManager.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "GLUtils.h"
#include "PointSetShapeDetection.h"

class MainWindow;

class GLWidget3D : public QGLWidget {
	Q_OBJECT

public:
	MainWindow* mainWin;

	// camera
	Camera camera;
	glm::vec3 light_dir;
	glm::mat4 light_mvpMatrix;
	glm::vec3 spot_light_pos;

	// input voxel data
	std::vector<std::pair<glm::vec3, glm::vec3>> point_cloud;
	std::vector<int> classification;
	std::vector<pointcloud::Face> detected_faces;

	// rendering engine
	RenderManager renderManager;

	bool show_points;
	bool show_faces;
	bool face_detected;
	int show_face_id = -1;
	
	// key status
	bool shiftPressed;
	bool ctrlPressed;

	bool first_paint;

public:
	GLWidget3D(MainWindow *parent = 0);

	void drawScene();
	void render();
	void showFace(int face_id);
	void loadVoxelData(const QString& filename);
	void convertVDB2PointCloud(std::vector<cv::Mat_<uchar>>& voxel_data, std::vector<std::pair<glm::vec3, glm::vec3>>& point_cloud, int threshold, float voxel_size);
	void detect(double probability, double min_points, double epsilon, double cluster_epsilon, double normal_threshold);
	void segment();
	float uniform_rand(float a, float b);
	glm::vec4 getColor(int index);
	void printDetectedFaces();
	void saveImage(const QString& filename);
	void update3DGeometry();
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent* e);
};
