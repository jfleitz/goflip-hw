/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PopBumper.h
 * Author: drjones
 *
 * Created on September 22, 2016, 9:30 PM
 */

#ifndef POPBUMPER_H
#define POPBUMPER_H

#include "BasePart.h"


class PopBumper : public BasePart {
public:
	PopBumper();
	PopBumper(const PopBumper& orig);
	virtual ~PopBumper();

	void queueAction();

private:

};

#endif /* POPBUMPER_H */

