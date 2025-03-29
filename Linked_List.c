#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.1415926
#define MAX_ATOMS 46

typedef struct AtomRecord {
struct AtomRecord *anext;
int AtomNumber;
char AtomName[4];
char Alternate;
char ResName[4];
char Chain;
int ResNumber;
double Coordx,Coordy,Coordz;
float Occupancy;
float Bfactor;
}Atom;

typedef struct ResidueRecord {
struct ResidueRecord *rnext;
	Atom *Natom;
	Atom *CAatom;
	Atom *Catom;
	Atom *Oatom;
	double TCO; //double or float
	double Kappa;
	double Alpha;
	double phi;
	double psi;
	Atom *CBatom;// 
	char ResName3[4];// 
	char ResName1;//
	int ResType;//
	int ResNumber;// 
int AtomCount;//
}Residue;

typedef struct ProteinRecord {
Atom *FirstAtom;
Atom *LastAtom;
Residue *FirstResidue;
Residue *LastResidue;
char PDBname[5];//
int AtomCount;//
int ResCount;//
int PepCount;//
} Protein;

Protein TestProtein;


float Distance(float x1, float y1, float z1, float x2, float y2, float z2){
	float x, y, z, d;
	x = x2-x1;
	y = y2-y1;
	z = z2-z1;
	d = sqrt(x*x+y*y+z*z);
	return (d);
}

float CosAngle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
	float r1x, r1y, r1z;
	float r2x, r2y, r2z;
	float bi, bk;
	float cosangle;
	
	r1x = x1-x2;
	r1y = y1-y2;
	r1z = z1-z2;
	
	r2x = x3-x4;
	r2y = y3-y4;
	r2z = z3-z4;
	
	bi=Distance(r1x, r1y, r1z, 0, 0, 0);
	bk=Distance(r2x, r2y, r2z, 0, 0, 0);
	
	if((bi==0)||(bk==0))
		cosangle=1;
	else
		cosangle=(r1x*r2x+r1y*r2y+r1z*r2z)/(bi*bk);
	
	return (cosangle);
}

float Angle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
	float r1x, r1y, r1z;
	float r2x, r2y, r2z;
	float bi, bk;
	float cosangle, ang;
	
	r1x = x1-x2;
	r1y = y1-y2;
	r1z = z1-z2;
	
	r2x = x3-x4;
	r2y = y3-y4;
	r2z = z3-z4;
	
	bi=Distance(r1x, r1y, r1z, 0, 0, 0);
	bk=Distance(r2x, r2y, r2z, 0, 0, 0);
	
	if((bi==0)||(bk==0))
		cosangle=1;
	else
		cosangle=(r1x*r2x+r1y*r2y+r1z*r2z)/(bi*bk);
	
	ang = (acos(cosangle)*180)/PI;
	
	return (ang);
}

float TorsionAngle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4)
{
	float r1x,r1y,r1z;
	float r2x,r2y,r2z;
	float p1x,p1y,p1z;
	float p2x,p2y,p2z;
	float q1x,q1y,q1z;
	float cosang,ang,sign;

	r1x=x1-x2;
	r1y=y1-y2;
	r1z=z1-z2;
	r2x=x3-x2;
	r2y=y3-y2;
	r2z=z3-z2;
	p1x=r1y*r2z-r1z*r2y;
	p1y=r1z*r2x-r1x*r2z;
	p1z=r1x*r2y-r1y*r2x;

	r1x=x2-x3;
	r1y=y2-y3;
	r1z=z2-z3;
	r2x=x4-x3;
	r2y=y4-y3;
	r2z=z4-z3;
	p2x=r1y*r2z-r1z*r2y;
	p2y=r1z*r2x-r1x*r2z;
	p2z=r1x*r2y-r1y*r2x;

	q1x=p1y*p2z-p1z*p2y;
	q1y=p1z*p2x-p1x*p2z;
	q1z=p1x*p2y-p1y*p2x;		
	r2x=x3-x2;
	r2y=y3-y2;
	r2z=z3-z2;	
	
	cosang=CosAngle(p1x,p1y,p1z,0,0,0,p2x,p2y,p2z,0,0,0);
	ang = (acos(cosang)*180)/PI;
	sign = q1x*r2x+q1y*r2y+q1z*r2z;
	if(sign>=0)
		return(ang);
	else
		return(-ang);		
}


void ReadPDB(char *PDBID){
	FILE *fptr;
	char *filepath = (char*)malloc(strlen(PDBID)+5);
	char *buffer = (char*)malloc(83);
	char *section = (char*)malloc(7);
	Atom *NewAtom;
	Atom *NAtom = NULL;
	Atom *CaAtom = NULL;
	Atom *CAtom = NULL;
	Atom *OAtom = NULL;
	char *atomn;
	char *resn;
	char *coord;
	char *occ;
	char *bf;
	Residue *NewResidue;
	
	sprintf(filepath, "%s.pdb", PDBID);
	fptr = fopen(filepath, "r");
	if (fptr == NULL)
	{
		printf("Can't open the file %s\n", filepath);
		free(filepath);        
		exit (1);
	}
	while(fgets(buffer,82,fptr) != NULL){
		strncpy(section, &buffer[0], 6);
		section[6] = '\0';
		if(strcmp(section, "ATOM  ")==0){
			NewAtom = (Atom*)malloc(sizeof(Atom));
			NewAtom -> anext = NULL;
			
			atomn = (char*)malloc(6);
			strncpy(atomn, &buffer[6], 5);
			atomn[5] = '\0';
			NewAtom -> AtomNumber = atoi(atomn);
			
			strncpy(NewAtom -> AtomName, &buffer[13], 3);
			NewAtom -> AtomName[3] = '\0';
			
			NewAtom -> Alternate = buffer[16];
			
			strncpy(NewAtom -> ResName, &buffer[17], 3);
			NewAtom -> ResName[3] = '\0';
			
			NewAtom -> Chain = buffer[21];
			
			resn = (char*)malloc(5);
			strncpy(resn, &buffer[22], 4);
			resn[4] = '\0';
			NewAtom -> ResNumber = atoi(resn);
			
			coord = (char*)malloc(9);
			strncpy(coord, &buffer[30], 8);
			coord[8] = '\0';
			NewAtom -> Coordx = atof(coord);
			
			strncpy(coord, &buffer[38], 8);
			coord[8] = '\0';
			NewAtom -> Coordy = atof(coord);
			
			strncpy(coord, &buffer[46], 8);
			coord[8] = '\0';
			NewAtom -> Coordz = atof(coord);
			
			occ = (char*)malloc(7);
			strncpy(occ, &buffer[54], 6);
			occ[6] = '\0';
			NewAtom -> Occupancy = atof(occ);
			
			bf = (char*)malloc(7);
			strncpy(bf, &buffer[60], 6);
			bf[6] = '\0';
			NewAtom -> Bfactor = atof(bf);
			
			if(TestProtein.LastAtom == NULL){
				TestProtein.FirstAtom = NewAtom;
				TestProtein.LastAtom = NewAtom;
			}
			else{
				TestProtein.LastAtom->anext=NewAtom;
				TestProtein.LastAtom=NewAtom;
			}
			if((NewAtom->AtomName[0]=='N') && (NewAtom -> AtomName[1] == ' ')){
				NAtom = NewAtom;
			}
			else if((NewAtom->AtomName[0]=='C') && (NewAtom -> AtomName[1] == 'A')){
				CaAtom = NewAtom;
			}
			else if((NewAtom->AtomName[0]=='C') && (NewAtom -> AtomName[1] == ' ')){
				CAtom = NewAtom;
			}
			else if((NewAtom->AtomName[0]=='O') && (NewAtom -> AtomName[1] == ' ')){
				OAtom = NewAtom;
			}
			if((NAtom!=NULL)&&(CAtom!=NULL)&&(CaAtom!=NULL)&&(OAtom!=NULL)&&(NAtom->ResNumber==CaAtom->ResNumber)&&(NAtom->ResNumber==CAtom->ResNumber)&&(NAtom->ResNumber==OAtom->ResNumber)&&(NAtom->ResNumber == TestProtein.ResCount+1)){
				NewResidue =(Residue*)malloc(sizeof(Residue)); //?
				NewResidue->Natom=NAtom;
				NewResidue->CAatom=CaAtom;
				NewResidue->Catom=CAtom;
				NewResidue->Oatom=OAtom;
				NewResidue->ResNumber=NAtom->ResNumber;
				NewResidue->rnext=NULL;
				
				if(TestProtein.LastResidue == NULL){
					TestProtein.FirstResidue = NewResidue;
					TestProtein.LastResidue = NewResidue;
					TestProtein.ResCount=1;
				}
				else{
					TestProtein.LastResidue->rnext=NewResidue;
					TestProtein.LastResidue=NewResidue;
					TestProtein.ResCount++;
				}
			}
		}
	}
	fclose(fptr);
	free(filepath);
} 

void CalTCO(){
	Residue *TempResidue;
	TestProtein.FirstResidue->TCO=0;
	for(TempResidue = TestProtein.FirstResidue; TempResidue->rnext; TempResidue = TempResidue->rnext){
		TempResidue->rnext->TCO=CosAngle(TempResidue->rnext->Catom->Coordx, TempResidue->rnext->Catom->Coordy, TempResidue->rnext->Catom->Coordz,
										 TempResidue->rnext->Oatom->Coordx, TempResidue->rnext->Oatom->Coordy, TempResidue->rnext->Oatom->Coordz,
										 TempResidue->Catom->Coordx, TempResidue->Catom->Coordy, TempResidue->Catom->Coordz,
										 TempResidue->Oatom->Coordx, TempResidue->Oatom->Coordy, TempResidue->Oatom->Coordz);
	}	
}

void CalKappa(){
	Residue *TempResidue;
	TestProtein.FirstResidue->Kappa=360;
	TestProtein.FirstResidue->rnext->Kappa=360;
	for(TempResidue = TestProtein.FirstResidue; TempResidue->rnext->rnext->rnext->rnext; TempResidue = TempResidue->rnext){
		TempResidue->rnext->rnext->Kappa=Angle(TempResidue->rnext->rnext->CAatom->Coordx, TempResidue->rnext->rnext->CAatom->Coordy, TempResidue->rnext->rnext->CAatom->Coordz,
											   TempResidue->CAatom->Coordx, TempResidue->CAatom->Coordy, TempResidue->CAatom->Coordz,
										 	   TempResidue->rnext->rnext->rnext->rnext->CAatom->Coordx, TempResidue->rnext->rnext->rnext->rnext->CAatom->Coordy, TempResidue->rnext->rnext->rnext->rnext->CAatom->Coordz,
											   TempResidue->rnext->rnext->CAatom->Coordx, TempResidue->rnext->rnext->CAatom->Coordy, TempResidue->rnext->rnext->CAatom->Coordz);						 		 
	}
	TempResidue->rnext->rnext->Kappa=360;
	TempResidue->rnext->rnext->rnext->Kappa=360;
}

void CalAlpha(){
	Residue *TempResidue;
	TestProtein.FirstResidue->Alpha=360;
	for(TempResidue = TestProtein.FirstResidue; TempResidue->rnext->rnext->rnext; TempResidue = TempResidue->rnext){
		TempResidue->rnext->Alpha=TorsionAngle(TempResidue->CAatom->Coordx, TempResidue->CAatom->Coordy, TempResidue->CAatom->Coordz,
											   TempResidue->rnext->CAatom->Coordx, TempResidue->rnext->CAatom->Coordy, TempResidue->rnext->CAatom->Coordz,
										 	   TempResidue->rnext->rnext->CAatom->Coordx, TempResidue->rnext->rnext->CAatom->Coordy, TempResidue->rnext->rnext->CAatom->Coordz,
											   TempResidue->rnext->rnext->rnext->CAatom->Coordx, TempResidue->rnext->rnext->rnext->CAatom->Coordy, TempResidue->rnext->rnext->rnext->CAatom->Coordz);						 		 
	}
	TempResidue->rnext->Alpha=360;
	TempResidue->rnext->rnext->Alpha=360;
}

void CalPhi(){
	Residue *TempResidue;
	TestProtein.FirstResidue->phi=360;
	for(TempResidue = TestProtein.FirstResidue; TempResidue->rnext; TempResidue = TempResidue->rnext){
		TempResidue->rnext->phi=TorsionAngle(TempResidue->Catom->Coordx, TempResidue->Catom->Coordy, TempResidue->Catom->Coordz, // C(i-1)
											 TempResidue->rnext->Natom->Coordx, TempResidue->rnext->Natom->Coordy, TempResidue->rnext->Natom->Coordz, // N(i)
											 TempResidue->rnext->CAatom->Coordx, TempResidue->rnext->CAatom->Coordy, TempResidue->rnext->CAatom->Coordz, // CA(i)
											 TempResidue->rnext->Catom->Coordx, TempResidue->rnext->Catom->Coordy, TempResidue->rnext->Catom->Coordz); // C(i) 
	}
}

void CalPsi(){
	Residue *TempResidue;
	for(TempResidue = TestProtein.FirstResidue; TempResidue->rnext; TempResidue = TempResidue->rnext){
		TempResidue->psi=TorsionAngle(TempResidue->Natom->Coordx, TempResidue->Natom->Coordy, TempResidue->Natom->Coordz, // N(i)
									  TempResidue->CAatom->Coordx, TempResidue->CAatom->Coordy, TempResidue->CAatom->Coordz, // CA(i)
									  TempResidue->Catom->Coordx, TempResidue->Catom->Coordy, TempResidue->Catom->Coordz, // C(i)
									  TempResidue->rnext->Natom->Coordx, TempResidue->rnext->Natom->Coordy, TempResidue->rnext->Natom->Coordz); // N(i+1) 
	}
	TempResidue->psi=360;
}

void PrintOutput(){
	FILE *outputFile = fopen("angle.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file for writing.\n");
    }

    Residue *TempResidue;
    for (TempResidue = TestProtein.FirstResidue; TempResidue; TempResidue = TempResidue->rnext) {
        fprintf(outputFile, "Residue %4d: TCO=%7.3f, Kappa=%7.1f, Alpha=%7.1f, phi=%7.1f, psi=%7.1f\n", TempResidue->ResNumber,
                TempResidue->TCO, TempResidue->Kappa, TempResidue->Alpha, TempResidue->phi, TempResidue->psi);
    }
    fclose(outputFile);
}

void CreateDistanceMatrix(){
    Residue *TempResidue;

    float** distanceMatrix = malloc(MAX_ATOMS * sizeof(float*));
    int i, j;
    for(i = 0; i < MAX_ATOMS; i++) {
        distanceMatrix[i] = malloc(MAX_ATOMS * sizeof(float));
    }
    
    for(i = 0; i < MAX_ATOMS; i++) {
        for(j = 0; j < MAX_ATOMS; j++) {
            distanceMatrix[i][j] = 0.0; 
        }
    }

    int r = 0;
    for(TempResidue = TestProtein.FirstResidue; TempResidue && r < MAX_ATOMS; TempResidue = TempResidue->rnext) 
    {
        int c = 0;
        Residue* TempResidue2;
        for(TempResidue2 = TestProtein.FirstResidue; TempResidue2 && c < MAX_ATOMS; TempResidue2 = TempResidue2->rnext) 
        {
            double d = Distance(TempResidue->CAatom->Coordx, TempResidue->CAatom->Coordy, TempResidue->CAatom->Coordz, TempResidue2->CAatom->Coordx, TempResidue2->CAatom->Coordy, TempResidue2->CAatom->Coordz);
            distanceMatrix[r][c] = d;
            c++;
        }
        r++;
    }

    FILE* file = fopen("dm.txt", "w");
    if(file == NULL){
        printf("Error opening file for writing.\n");
    }

    fprintf(file, "%3s", "");
    for(i = 1; i <= MAX_ATOMS; i++) {
        fprintf(file, "%3d", i);
    }
    fprintf(file, "\n");

    for(i = 0; i < MAX_ATOMS; i++) {
        fprintf(file, "%3d", i + 1);
        for(j = 0; j < MAX_ATOMS; j++) {
            int dm = round(distanceMatrix[i][j]);
            if( dm > 9)
            {
                fprintf(file, "%3s", ".");
            }
            else
            {
                fprintf(file, "%3d", dm);    
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(){
	TestProtein.FirstResidue = NULL;
	TestProtein.LastResidue = NULL;
	TestProtein.FirstAtom = NULL;
	TestProtein.LastAtom = NULL;
	ReadPDB("1crn");
	
	CalTCO();
	CalKappa();
	CalAlpha();
	CalPhi();
	CalPsi();
	
	PrintOutput();
	CreateDistanceMatrix();
	return 0;
} 
