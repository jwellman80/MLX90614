/*

MLX90614 library created from example from:
http://bildr.org/2011/02/mlx90614-arduino/

Library Created by:
	Jared Wellman - jared@mainsequencesoftware.com
	Created Date: 2013/10/13
	Last Modified: 2013/10/19
*/



#ifndef __MLX90614__H_
#define __MLX90614__H_

class MLX90614
{
private:
	float GetTemp(int type);

public:
	MLX90614();
	float GetTempAmbient(char t = 'C');
	float GetTempIR(char t = 'C');
};

#endif
