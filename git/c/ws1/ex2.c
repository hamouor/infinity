float Powr(int n){
	int i;
	float res;
	float oper;
	oper = 10.0;
	res = 1.0; /*result initialized to 1*/
	
/*check for negative power*/
	if (n<0){
		n=-n;
		oper = 0.1;
		}

	for (i=0; i<n; i++){
		res=res*oper;
	}	
	return res;
}

