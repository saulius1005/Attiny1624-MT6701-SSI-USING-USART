/*
 * MT6701Var.h
 *
 * Created: 2025-02-28 18:10:17
 *  Author: Saulius
 */ 


#ifndef MT6701VAR_H_
#define MT6701VAR_H_

AngleSensorStatus MT6701 ={
.Angle = 0.0, 
.MagneticFieldStatus = 0, //0- Normal, 1- Magnetic Field is too Strong, 2- Magnetic Field is too Weak
.PushButtonStatus = 0, // 0- Normal, 1- Push Button is Detected
.TrackStatus = 0, // 0- Normal, 1- Loss of Track
.CRCError = 0 // 0- Normal, 1- CRC Error
};

#endif /* MT6701VAR_H_ */