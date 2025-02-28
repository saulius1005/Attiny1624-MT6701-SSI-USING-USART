/*
 * MT6701.h
 *
 * Created: 2025-02-28 18:10:05
 *  Author: Saulius
 */ 


#ifndef MT6701_H_
#define MT6701_H_

typedef struct {
    double Angle;
	uint8_t MagneticFieldStatus;
	uint8_t PushButtonStatus;
	uint8_t TrackStatus;
	uint8_t CRCError;
} AngleSensorStatus;

extern AngleSensorStatus MT6701;

#endif /* MT6701_H_ */