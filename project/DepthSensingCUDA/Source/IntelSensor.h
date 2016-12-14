#pragma once

/************************************************************************/
/* Intel Sensor                                                         */
/************************************************************************/

#include "GlobalAppState.h"

#ifdef INTEL_SENSOR

#include "RGBDSensor.h"
#include "DSAPI.h"
#include "DSAPIUtil.h"

class IntelSensor : public RGBDSensor
{
public:
	IntelSensor();
	//! Constructor; allocates CPU memory and creates handles

	//! Destructor; releases allocated ressources
	virtual ~IntelSensor() override;

	//! Initializes the sensor
	virtual HRESULT createFirstConnected() override;

	//! process the data for next frame
	virtual HRESULT process() override;

	virtual std::string getSensorName() const override{
		return "IntelSensor";
	}

private:

	//! gets the next depth frame
	HRESULT processDepth();

	//! must call process depth before process color, always returns last color frame
	//! maps the color to depth data
	HRESULT processColor();


	DSAPI*			m_sensor;
	DSThird*		m_colorSensor;
	DSHardware*		m_hardware;

	// camera parameters
	int				m_depthFPS;
	int				m_colorFPS;
	float			m_exposure;
	float			m_gain;
	mat4f			m_intrinsicsDepth;
	mat4f			m_intrinsicsColor;
	mat4f			m_intrinsicsColorInv;
	mat4f			m_extrinsicsColorToDepth; // translation only

	unsigned int	m_depthFrameNumber;
	unsigned int	m_colorFrameNumber;

	// to prevent drawing until we have data for both streams
	bool			m_bDepthReceived;
	bool			m_bColorReceived;
};

#endif