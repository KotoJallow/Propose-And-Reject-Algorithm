#include "proposeAndRejectAlgorithm.h"
#include <cstdlib>
#include <ctime>

struct m
{
	enum{
		Victor = 86,Wyatt,Xavier,Yancey,Zeus
	}; 
} ;
struct w
{
	enum {
		Amy = 97, Bertha,Clare,Diane,Erika	
	};
};

int main(){
	Graph gMen,gWomen;
	
	//Start Men's Preference Profile
	gMen.insert(m::Victor,w::Bertha);gMen.insert(m::Victor,w::Amy);gMen.insert(m::Victor,w::Diane);
	gMen.insert(m::Victor,w::Erika);gMen.insert(m::Victor,w::Clare);

	gMen.insert(m::Wyatt,w::Diane);gMen.insert(m::Wyatt,w::Bertha);gMen.insert(m::Wyatt,w::Amy);
	gMen.insert(m::Wyatt,w::Clare);gMen.insert(m::Wyatt,w::Erika);

	gMen.insert(m::Xavier,w::Bertha);gMen.insert(m::Xavier,w::Erika);gMen.insert(m::Xavier,w::Clare);
	gMen.insert(m::Xavier,w::Diane);gMen.insert(m::Xavier,w::Amy);

	gMen.insert(m::Yancey,w::Amy);gMen.insert(m::Yancey,w::Diane);gMen.insert(m::Yancey,w::Clare);
	gMen.insert(m::Yancey,w::Bertha);gMen.insert(m::Yancey,w::Erika);

	gMen.insert(m::Zeus,w::Bertha);gMen.insert(m::Zeus,w::Diane);gMen.insert(m::Zeus,w::Amy);
	gMen.insert(m::Zeus,w::Erika);gMen.insert(m::Zeus,w::Clare);

	//end of filling Men's Preference Profile

	//Begin Women's Preference Profile
	gWomen.insert(w::Amy,m::Zeus);gWomen.insert(w::Amy,m::Victor);gWomen.insert(w::Amy,m::Wyatt);
	gWomen.insert(w::Amy,m::Yancey);gWomen.insert(w::Amy,m::Xavier);

	gWomen.insert(w::Bertha,m::Xavier);gWomen.insert(w::Bertha,m::Wyatt);gWomen.insert(w::Bertha,m::Yancey);
	gWomen.insert(w::Bertha,m::Victor);gWomen.insert(w::Bertha,m::Zeus);

	gWomen.insert(w::Clare,m::Wyatt);gWomen.insert(w::Clare,m::Xavier);gWomen.insert(w::Clare,m::Yancey);
	gWomen.insert(w::Clare,m::Zeus);gWomen.insert(w::Clare,m::Victor);

	gWomen.insert(w::Diane,m::Victor);gWomen.insert(w::Diane,m::Zeus);gWomen.insert(w::Diane,m::Yancey);
	gWomen.insert(w::Diane,m::Xavier);gWomen.insert(w::Diane,m::Wyatt);

	gWomen.insert(w::Erika,m::Yancey);gWomen.insert(w::Erika,m::Wyatt);gWomen.insert(w::Erika,m::Zeus);
	gWomen.insert(w::Erika,m::Xavier);gWomen.insert(w::Erika,m::Victor);

	//end of filling Women's Preference Profile

	gMen.stableMatch(gWomen);

	cout << "Men's Marriage Partners" << endl;
	gMen.displayStableMatch();
	cout << "Women's Marriage Partners" << endl;
	gWomen.displayStableMatch();

	return 0;
}
