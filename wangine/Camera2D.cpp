#include "Camera2D.h"


namespace wangine {
	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_screenWidth(500),
		_screenHight(500)
	{}

	void Camera2D::init(int screenWidth, int screenHight)
	{
		_screenWidth = screenWidth;
		_screenHight = screenHight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHight);

		_needsMatrixUpdate = true;
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;


			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::ConvertScreen2World(glm::vec2 screenCoord)
	{
		//inverting y coords
		screenCoord.y = _screenHight - screenCoord.y;
		//makes center = 0
		screenCoord -= glm::vec2(_screenWidth / 2, _screenHight / 2);
		//scale the coordinates
		screenCoord /= _scale;
		//translate with camera pos
		screenCoord += _position;

		return screenCoord;
	}
}