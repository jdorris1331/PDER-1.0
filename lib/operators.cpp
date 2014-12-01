#include "operators.h"

VAR* ustp(VAR* A) {
	VAR* ret_var = new VAR;
	int type = A->get_type();
	ret_var->set_type(type);	
	if(type == 2){
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					for(int v = 0; v < 3; v++){
						if(A->vf[x][y][z][v] > 0) ret_var->vf[x][y][z][v] = 1.0;
						else ret_var->vf[x][y][z][v] = 0.0;
					}
				}
			}
		}
	}
	else if(type == 1){
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					if(A->sf[x][y][z] > 0) ret_var->sf[x][y][z] = 1.0;
					else ret_var->sf[x][y][z] = 0.0;
				}
			}
		}
	}
	else if(type == 0){
		if(A->val > 0) ret_var->val = 1.0;
		else ret_var->val = 0.0;
	}
	delete A;
	return ret_var;
}

VAR* rand(VAR* A){
	srand(time(NULL));
	VAR* ret_var = new VAR;
	int type = A->get_type();
	ret_var->set_type(type);	
	if(type == 2){
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					for(int v = 0; v < 3; v++){
						ret_var->vf[x][y][z][v] = (double)rand();
					}
				}
			}
		}
	}
	else if(type == 1){
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = (double)rand();
				}
			}
		}
	}
	else if(type == 0){
		ret_var->val = (double)rand();
	}
	delete A;
	return ret_var;
}

VAR* add(VAR* A, VAR* B) {
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  int type2 = B->get_type();
  if(type1==0 && type2==0) {
    ret_var->set_type(0);
    ret_var->val = A->val + B->val;
  }
  if(type1 == 2 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] + B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 1){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] + B->sf[x][y][z];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->sf[x][y][z] + B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 0){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] + B->val;
				}
			}
		}
	}
  }
  if(type1 == 0 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->val + B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 1){
	ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				ret_var->sf[x][y][z] = A->sf[x][y][z] + B->sf[x][y][z];
			}
		}
	}
  }
  if((type1 == 1 && type2 == 0)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->sf[x][y][z] + B->val;
				}
			}
		}
	}
  if((type1 == 0 && type2 == 1)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->val + B->sf[x][y][z];
				}
			}
		}
	}
	delete A;
	delete B;
	return ret_var;
}

VAR* sub(VAR* A, VAR* B) {
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  int type2 = B->get_type();
  if(type1==0 && type2==0) {
    ret_var->set_type(0);
    ret_var->val = A->val - B->val;
  }
  if(type1 == 2 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] - B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 1){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] - B->sf[x][y][z];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->sf[x][y][z] - B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 0){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] - B->val;
				}
			}
		}
	}
  }
  if(type1 == 0 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->val - B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 1){
	ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				ret_var->sf[x][y][z] = A->sf[x][y][z] - B->sf[x][y][z];
			}
		}
	}
  }
  if((type1 == 1 && type2 == 0)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->sf[x][y][z] - B->val;
				}
			}
		}
	}
  if((type1 == 0 && type2 == 1)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->val - B->sf[x][y][z];
				}
			}
		}
	}
	delete A;
	delete B;
	return ret_var;
}


VAR* mult(VAR* A, VAR* B) {
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  int type2 = B->get_type();
  if(type1==0 && type2==0) {
    ret_var->set_type(0);
    ret_var->val = A->val * B->val;
  }
  if(type1 == 2 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] * B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 1){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] * B->sf[x][y][z];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->sf[x][y][z] * B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 0){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->vf[x][y][z][v] * B->val;
				}
			}
		}
	}
  }
  if(type1 == 0 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = A->val * B->vf[x][y][z][v];
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 1){
	ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				ret_var->sf[x][y][z] = A->sf[x][y][z] * B->sf[x][y][z];
			}
		}
	}
  }
  if((type1 == 1 && type2 == 0)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->sf[x][y][z] * B->val;
				}
			}
		}
	}
  if((type1 == 0 && type2 == 1)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = A->val * B->sf[x][y][z];
				}
			}
		}
	}
	delete A;
	delete B;
	return ret_var;
}

VAR* divide(VAR* A, VAR* B) {
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  int type2 = B->get_type();
  if(type1==0 && type2==0) {
    ret_var->set_type(0);
		if(B->val != 0) ret_var->val = A->val/B->val;
		else {
			ret_var->set_type(-1);
			return ret_var;
		}
  }
  if(type1 == 2 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(B->vf[x][y][z][v] != 0) ret_var->vf[x][y][z][v] = A->vf[x][y][z][v]/B->vf[x][y][z][v];
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 1){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(B->sf[x][y][z] != 0) ret_var->vf[x][y][z][v] = A->vf[x][y][z][v]/B->sf[x][y][z];
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(B->vf[x][y][z][v] != 0) ret_var->vf[x][y][z][v] = A->sf[x][y][z]/B->vf[x][y][z][v];
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 0){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(B->val != 0) ret_var->vf[x][y][z][v] = A->vf[x][y][z][v]/B->val;
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  }
  if(type1 == 0 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(B->vf[x][y][z][v] != 0) ret_var->vf[x][y][z][v] = A->val/B->vf[x][y][z][v];
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 1){
	ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				if(B->sf[x][y][z] != 0) ret_var->sf[x][y][z] = A->sf[x][y][z]/B->sf[x][y][z];
				else {
					ret_var->set_type(-1);
					return ret_var;
				}
			}
		}
	}
  }
  if((type1 == 1 && type2 == 0)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					if(B->val != 0) ret_var->sf[x][y][z] = A->sf[x][y][z]/B->val;
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
  if((type1 == 0 && type2 == 1)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					if(B->sf[x][y][z] != 0) ret_var->sf[x][y][z] = A->val / B->sf[x][y][z];
					else {
						ret_var->set_type(-1);
						return ret_var;
					}
				}
			}
		}
	}
	delete A;
	delete B;
	return ret_var;
}


VAR* vmod(VAR* A, VAR* B) {
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  int type2 = B->get_type();
  if(type1==0 && type2==0) {
    ret_var->set_type(0);
    ret_var->val = static_cast<int>(A->val) % static_cast<int>(B->val);
  }
  if(type1 == 2 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = static_cast<int>(A->vf[x][y][z][v]) % static_cast<int>(B->vf[x][y][z][v]);
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 1){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = static_cast<int>(A->vf[x][y][z][v]) % static_cast<int>(B->sf[x][y][z]);
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = static_cast<int>(A->sf[x][y][z]) % static_cast<int>(B->vf[x][y][z][v]);
				}
			}
		}
	}
  }
  if(type1 == 2 && type2 == 0){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = static_cast<int>(A->vf[x][y][z][v]) % static_cast<int>(B->val);
				}
			}
		}
	}
  }
  if(type1 == 0 && type2 == 2){
	ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = static_cast<int>(A->val) % static_cast<int>(B->vf[x][y][z][v]);
				}
			}
		}
	}
  }
  if(type1 == 1 && type2 == 1){
	ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				ret_var->sf[x][y][z] = static_cast<int>(A->sf[x][y][z]) % static_cast<int>(B->sf[x][y][z]);
			}
		}
	}
  }
  if((type1 == 1 && type2 == 0)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = static_cast<int>(A->sf[x][y][z]) % static_cast<int>(B->val);
				}
			}
		}
	}
  if((type1 == 0 && type2 == 1)){
	ret_var->set_type(1);
		for(int x = 0; x < DIM_SIZE; x++){
			for(int y = 0; y < DIM_SIZE; y++){
				for(int z = 0; z < DIM_SIZE; z++){
					ret_var->sf[x][y][z] = static_cast<int>(A->val) % static_cast<int>(B->sf[x][y][z]);
				}
			}
		}
	}
	delete A;
	delete B;
	return ret_var;
}

double cdf(VAR* A, int x, int y, int z, int v, int d){ //d is the derivative respect

	if(d == 0 && x != 0 && x != DIM_SIZE-1) return (A->vf[x+1][y][z][v] - A->vf[x-1][y][z][v])/2;
	else if(d == 0 && x == 0) return (A->vf[x+1][y][z][v] - 0)/2;
	else if(d == 0 && x == DIM_SIZE-1) return (0 - A->vf[x-1][y][z][v])/2;

	if(d == 1 && y != 0 && y != DIM_SIZE-1) return (A->vf[x][y+1][z][v] - A->vf[x][y-1][z][v])/2;
	else if(d == 1 && y == 0) return (A->vf[x][y+1][z][v] - 0)/2;
	else if(d == 1 && y == DIM_SIZE-1) return (0 - A->vf[x][y-1][z][v])/2;
	
	if(d == 2 && z != 0 && z != DIM_SIZE-1) return (A->vf[x][y][z+1][v] - A->vf[x][y][z-1][v])/2;
	else if(d == 2 && z == 0) return (A->vf[x][y][z+1][v] - 0)/2;
	else if(d == 2 && z == DIM_SIZE-1) return (0 - A->vf[x][y][z-1][v])/2;

return 0;
}

double sdiff(VAR* A, int x, int y, int z, int d){ //sdiff is the differentiation function for scalar fields.  It's basically the same as cdf.

  if(d == 0 && x != 0 && x != DIM_SIZE-1) return (A->sf[x+1][y][z] - A->sf[x-1][y][z])/2;
  else if(d == 0 && x == 0) return (A->sf[x+1][y][z] - 0)/2;
  else if(d == 0 && x == DIM_SIZE-1) return (0 - A->sf[x-1][y][z])/2;

  if(d == 1 && y != 0 && y != DIM_SIZE-1) return (A->sf[x][y+1][z] - A->sf[x][y-1][z])/2;
  else if(d == 1 && y == 0) return (A->sf[x][y+1][z] - 0)/2;
  else if(d == 1 && y == DIM_SIZE-1) return (0 - A->sf[x][y-1][z])/2;

  if(d == 2 && z != 0 && z != DIM_SIZE-1) return (A->sf[x][y][z+1] - A->sf[x][y][z-1])/2;
  else if(d == 2 && z == 0) return (A->sf[x][y][z+1] - 0)/2;
  else if(d == 2 && z == DIM_SIZE-1) return (0 - A->sf[x][y][z-1])/2;

return 0;
}

VAR* grad(VAR* A) {
  VAR * ret_var = new VAR;
  int type1 = A->get_type();
  if(type1 == 0 || type1 == 2){ ret_var->set_type(-1); }
  else if(type1==1){
  ret_var->set_type(2);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					ret_var->vf[x][y][z][v] = sdiff(A,x,y,z,v);
				}
			}
		}
	}
  }
	delete A; 
  return ret_var;
}

VAR* curl(VAR* A){
	VAR* ret_var = new VAR;
  int type1 = A->get_type();
  ret_var->set_type(type1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				for(int v = 0; v < 3; v++){
					if(v == 0) ret_var->vf[x][y][z][v] = cdf(A,x,y,z,2,1) - cdf(A,x,y,z,1,2);
					if(v == 1) ret_var->vf[x][y][z][v] = cdf(A,x,y,z,0,2) - cdf(A,x,y,z,2,0);
					if(v == 2) ret_var->vf[x][y][z][v] = cdf(A,x,y,z,1,0) - cdf(A,x,y,z,0,1);
				}
			}
		}
	}
	delete A;
	return ret_var;
}

VAR* diverg(VAR* A){
	VAR* ret_var = new VAR;
  int type1 = A->get_type();
  if(type1==0 || type1==1) ret_var->set_type(-1);
  else {
  ret_var->set_type(1);
	for(int x = 0; x < DIM_SIZE; x++){
		for(int y = 0; y < DIM_SIZE; y++){
			for(int z = 0; z < DIM_SIZE; z++){
				ret_var->sf[x][y][z] = cdf(A,x,y,z,0,0) + cdf(A,x,y,z,1,1) + cdf(A,x,y,z,2,2);
			}
		}
	}
   }
	delete A;
	return ret_var;
}

/*double LDF(VAR* A, int x, int y, int z, int v, int d){ //d is the derivative respect

        if(d == 0 && x != 0 && x != DIM_SIZE-1) return (A->vf[x+1][y][z][v] + A->vf[x-1][y][z][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 0 && x == 0) return (A->vf[x+1][y][z][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 0 && x == DIM_SIZE-1) return (A->vf[x-1][y][z][v] - (2*(A->vf[x][y][z][v])));

        if(d == 1 && y != 0 && y != DIM_SIZE-1) return (A->vf[x][y+1][z][v] + A->vf[x][y-1][z][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 1 && y == 0) return (A->vf[x][y+1][z][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 1 && y == DIM_SIZE-1) return (A->vf[x][y-1][z][v] - (2*(A->vf[x][y][z][v])));

        if(d == 2 && z != 0 && z != DIM_SIZE-1) return (A->vf[x][y][z+1][v] + A->vf[x][y][z-1][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 2 && z == 0) return (A->vf[x][y][z+1][v] - (2*(A->vf[x][y][z][v])));
        else if(d == 2 && z == DIM_SIZE-1) return (A->vf[x][y][z-1][v] - (2*(A->vf[x][y][z][v])));

return 0;
}

VAR* laplac(VAR* A){
  VAR* ret_var = new VAR;
  int type1 = A->get_type();
  if(type1 == 0 || type1 == 1) ret_var->set_type(-1);
  else {
    ret_var->set_type(1);
        for(int x = 0; x < DIM_SIZE; x++){
                for(int y = 0; y < DIM_SIZE; y++){
                        for(int z = 0; z < DIM_SIZE; z++){
                                ret_var->sf[x][y][z] = LDF(A,x,y,z,0,0) + LDF(A,x,y,z,1,1) + LDF(A,x,y,z,2,2);
                        }
                }
        }
  }
        delete A;
        return ret_var;
}*/
	
VAR* laplac(VAR* A){
	VAR* temp;
	VAR* ret_var;
	temp = grad(A);
	ret_var = diverg(temp);
	return ret_var;
}

VAR* mag(VAR* A) {
  VAR * ret_var = new VAR;
  double temp=0;
  int type1 = A->get_type();
  if(type1 == 0 || type1 == 1){ ret_var->set_type(-1); }
  else if(type1==2){
  ret_var->set_type(1);
  for(int x = 0; x < DIM_SIZE; x++){
    for(int y = 0; y < DIM_SIZE; y++){
      for(int z = 0; z < DIM_SIZE; z++){
        for(int v = 0; v < 3; v++){
          temp+=(A->vf[x][y][z][v])*(A->vf[x][y][z][v]);
        }
        ret_var->sf[x][y][z] = sqrt(temp);
        temp=0;
      }
    }
  }
  }
  delete A;
  return ret_var;
}

