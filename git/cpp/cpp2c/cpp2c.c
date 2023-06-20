#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum{
    Dtor = 0,
    Display = 1
};

typedef void (*func)(void*);

int s_count = 0;

void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

typedef struct a
{
	func virtuals[2];/*point to the right virtuals array*/
	int m_license_plate;
}Public_Transport;


void Public_Transport_Display(void* pub)
{
    ((((Public_Transport*)pub)->virtuals)[Display])(pub);
}

void Public_Transport_Dtor(void* this_)
{
	--s_count;
    Public_Transport* temp = (Public_Transport*)this_;
    printf("Public_Transport::Dtor()%d\n", temp->m_license_plate);

}

void Virtual_Public_Transport_Display(void* this_)
{
    Public_Transport* temp = (Public_Transport*)this_;
    printf("Public_Transport::Display(): %d\n", temp->m_license_plate);
}

void Public_Transport_Ctor(Public_Transport* this_)
{
	++s_count;
	this_->m_license_plate = s_count;
    this_->virtuals[Display] = &Virtual_Public_Transport_Display;
    this_->virtuals[Dtor] = &Public_Transport_Dtor;
    printf("Public_Transport::Ctor()%d\n", this_->m_license_plate);
}

void Public_Transport_CCtor(Public_Transport* this_, Public_Transport* other_)
{
	++s_count;
	this_->m_license_plate = s_count;
    this_->virtuals[Display] = &Virtual_Public_Transport_Display;
    this_->virtuals[Dtor] = &Public_Transport_Dtor;
    printf("Public_Transport::CCtor() %d\n", this_->m_license_plate);
}

int GetID(Public_Transport* this_)
{
	return this_->m_license_plate;
}

typedef struct b
{
    Public_Transport pub;
    int m_numSeats;
  	func virtuals[2];/*no need - just set pub for the right functions*/
}Minibus;

void Minibus_Display(void* this_)
{
    Minibus* temp = (Minibus*)this_;
    printf("Minibus::Display() ID:%d num seats:%d\n", GetID(&temp->pub), temp->m_numSeats);
}

void Minibus_Dtor(void* this_)
{
    Minibus* temp = (Minibus*)this_;
    printf("Minibus::dtor()\n");
    Public_Transport_Dtor(&temp->pub);
}

void Minibus_Ctor(Minibus* this_)
{
    Public_Transport_Ctor(&(this_->pub));
    this_->m_numSeats = 20;
    this_->pub.virtuals[Display] = Minibus_Display;
    this_->pub.virtuals[Dtor] = Minibus_Dtor;    
    printf("Minibus::Ctor()\n");
}


void Minibus_CCtor(Minibus* this_, Minibus* other_)
{
    Public_Transport_CCtor(&this_->pub, &other_->pub);
    this_->m_numSeats = other_->m_numSeats;
    this_->virtuals[Display] = Minibus_Display;
    this_->pub.virtuals[Display] = Minibus_Display;
    this_->virtuals[Dtor] = Minibus_Dtor;
    this_->pub.virtuals[Dtor] = Minibus_Dtor;   
    printf("Minibus::CCtor()\n");
}

                                            /*TODO WASH*/


typedef struct c
{
    Public_Transport pub;
    int m_numSeats;
    func virtuals[2];
}Taxi;

void Taxi_Display(void* this_)
{
    Taxi* temp = (Taxi*)this_;
    printf("Taxi::Display() ID:%d\n", GetID(&temp->pub));
}

void Taxi_Dtor(void* this_)
{
    Taxi* temp = (Taxi*)this_;
    printf("Taxi::dtor()\n");
    Public_Transport_Dtor(&temp->pub);
}

void Taxi_Ctor(Taxi* this_)
{
    Public_Transport_Ctor(&this_->pub);
    this_->virtuals[Display] = Taxi_Display;
    this_->pub.virtuals[Display] = Taxi_Display;
    this_->virtuals[Dtor] = Taxi_Dtor;
    this_->pub.virtuals[Dtor] = Taxi_Dtor;
    printf("Taxi::Ctor()\n");
}

void Taxi_CCtor(Taxi* this_, Taxi* other_)
{
    Public_Transport_CCtor(&this_->pub, &other_->pub);
    this_->virtuals[Display] = Taxi_Display;
    this_->pub.virtuals[Display] = Taxi_Display;
    this_->virtuals[Dtor] = Taxi_Dtor;
    this_->pub.virtuals[Dtor] = Taxi_Dtor;
    printf("Taxi::CCtor()\n");
}


int maxFuncInt(const int t1, const int t2)/*macro*/
{
	return ((t1 > t2)? t1: t2);
}


typedef struct e
{
    Taxi tax;
    func virtuals[2];
}Special_Taxi;

void Special_Taxi_Dtor(void* this_)
{
    Special_Taxi* temp = (Special_Taxi*)this_;
    printf("Special_Taxi::dtor()\n");
    Taxi_Dtor(&temp->tax);
}

void Special_Taxi_Display(void* spex)
{
    Special_Taxi* temp = (Special_Taxi*)spex;
    printf("Special_Taxi::Display() ID:%d\n", GetID(&temp->tax.pub));
}
void Special_Taxi_Ctor(Special_Taxi* this_)
{
    Taxi_Ctor(&this_->tax);
    this_->virtuals[Display] = Special_Taxi_Display;
    this_->tax.virtuals[Display] = Special_Taxi_Display;
    this_->tax.pub.virtuals[Display] = Special_Taxi_Display;
    this_->virtuals[Dtor] = Special_Taxi_Display;
    this_->tax.virtuals[Dtor] = Special_Taxi_Dtor;
    this_->tax.pub.virtuals[Dtor] = Special_Taxi_Dtor;
    printf("Special_Taxi::Ctor()\n");
}

void Special_Taxi_CCtor(Special_Taxi* this_, Special_Taxi* other_)
{
    Taxi_CCtor(&this_->tax, &other_->tax);
    this_->virtuals[Display] = Special_Taxi_Display;
    this_->tax.virtuals[Display] = Special_Taxi_Display;
    this_->tax.pub.virtuals[Display] = Special_Taxi_Display;
    this_->virtuals[Dtor] = Special_Taxi_Display;
    this_->tax.virtuals[Dtor] = Special_Taxi_Dtor;
    this_->tax.pub.virtuals[Dtor] = Special_Taxi_Dtor;
    printf("Special_Taxi::CCtor()\n");
}


typedef struct f
{
    Public_Transport pub;
    Public_Transport* m_pt1;
    Public_Transport* m_pt2;
    Minibus m_m;
    Taxi m_t;
    func virtuals[2];
}Public_Convoy;

void Public_Convoy_Display(void* pub)
{
    Public_Convoy* temp = (Public_Convoy*)pub;
    temp->m_pt1->virtuals[Display](temp->m_pt1);
    temp->m_pt2->virtuals[Display](temp->m_pt2);
    temp->m_m.virtuals[Display](&temp->m_m);
    temp->m_t.virtuals[Display](&temp->m_t);
}

void Public_Convoy_Dtor(Public_Convoy* this_)
{
    this_->m_pt1->virtuals[Dtor](this_->m_pt1);
    this_->m_pt2->virtuals[Dtor](this_->m_pt2);

    free(this_->m_pt1);
    free(this_->m_pt2);

    this_->m_t.virtuals[Dtor](&this_->m_t);
    this_->m_m.virtuals[Dtor](&this_->m_m);
    
    Public_Transport_Dtor(&this_->pub);

}

void Public_Convoy_Ctor(Public_Convoy* this_)
{
    Public_Transport_Ctor(&this_->pub);
    
    this_->m_pt1 = (Public_Transport*)malloc(sizeof(Minibus));
    Minibus_Ctor((Minibus*)this_->m_pt1);

    this_->m_pt2 = (Public_Transport*)malloc(sizeof(Taxi));
    Taxi_Ctor((Taxi*)this_->m_pt2);

    Minibus_Ctor(&this_->m_m);
    Taxi_Ctor(&this_->m_t);

    this_->virtuals[Display] = Public_Convoy_Display;
    this_->pub.virtuals[Display] = Public_Convoy_Display;
    this_->virtuals[Dtor] = Public_Convoy_Dtor;
    this_->pub.virtuals[Dtor] = Public_Convoy_Dtor;
}

void Public_Convoy_CCtor(Public_Convoy* this_, Public_Convoy* other_)
{
    Public_Transport_Ctor(&this_->pub);
    
    this_->m_pt1 = (Public_Transport*)malloc(sizeof(Minibus));
    Minibus_CCtor((Minibus*)this_->m_pt1, (Minibus*)other_->m_pt1);

    this_->m_pt2 = (Public_Transport*)malloc(sizeof(Taxi));
    Taxi_CCtor((Taxi*)this_->m_pt2, (Taxi*)other_->m_pt2);

    Minibus_Ctor(&this_->m_m);/*fix both cpp and this to cctor*/
    Taxi_Ctor(&this_->m_t);

    this_->virtuals[Display] = Public_Convoy_Display;
    this_->pub.virtuals[Display] = Public_Convoy_Display;
    this_->virtuals[Dtor] = Public_Convoy_Dtor;
    this_->pub.virtuals[Dtor] = Public_Convoy_Dtor;
}


void PrintInfoP(Public_Transport* a)
{
    a->virtuals[Display](a); 
}

void PrintInfo() 
{
    PrintCount(); 
}

Public_Transport* PrintInfoi(int i, Public_Transport* ret)/*accept public transport*/
{
    Minibus m;
    Minibus_Ctor(&m);
    
    printf("PrintInfo(int i)\n");
	Minibus_Display(&m);
    Public_Transport_CCtor(ret, (Public_Transport*)&m);
    Minibus_Dtor(&m);
    return ret;
}

void TaxiDisplay(Taxi s) /*ponter to taxi. cctor dtor*/
{
    Taxi_Display(&s);
}

int main()
{
    Minibus m, m1, m2;
    Public_Transport p;
    Taxi t, t1, t2;
    int i;
    Public_Transport arr2[3];
    Minibus arr3[4];
    Taxi* arr4;
    Special_Taxi st;
    Public_Convoy* ts1, *ts2;
    
    Minibus_Ctor(&m);
    
    PrintInfoP((Public_Transport*)&m);

    Minibus_Ctor(&m1);

    Public_Transport_CCtor(&p, PrintInfoi(3, &m1));

    m1.virtuals[Dtor](&m1);

    p.virtuals[Display](&p);

    p.virtuals[Dtor](&p);

    Public_Transport* array[3];

    array[0] = malloc(sizeof(Minibus));
    Minibus_Ctor((Minibus*)array[0]);

    array[1] = malloc(sizeof(Taxi));
    Taxi_Ctor((Taxi*)array[1]);

    array[2] = malloc(sizeof(Minibus));
    Minibus_Ctor((Minibus*)array[2]);

    for(i = 0; i < 3; ++i)
    {
        array[i]->virtuals[Display](array[i]);
    }

    for(i = 0; i < 3; ++i)
    {
        array[i]->virtuals[Dtor](array[i]);
        free(array[i]);
    }
 
    Minibus_Ctor(&m1);
    Public_Transport_CCtor(&(arr2[0]), (Public_Transport*)&m1);
    m1.virtuals[Dtor](&m1);

    Taxi_Ctor(&t1);
    Public_Transport_CCtor(&(arr2[1]), (Public_Transport*)&t1);
    t1.virtuals[Dtor](&t1);

    Public_Transport_Ctor(&(arr2[2]));

    for(i = 0; i < 3; ++i)
    {
        arr2[i].virtuals[Display](&arr2[i]);/*no need for v*/
    }

    PrintCount();

    Minibus_Ctor(&m2);

    PrintCount();

    for(i = 0; i < 4; ++i)
    {
        Minibus_Ctor(&arr3[i]);
    }

    arr4 = malloc(4 * sizeof(Taxi));

    for(i = 0; i < 4; ++i)
    {
        Taxi_Ctor(arr4 + i);
    }

    for(i = 3; i >= 0; --i)
    {
        (arr4 + i)->virtuals[Dtor](arr4 + i);
    }

    free(arr4);

    printf("%d\n", maxFuncInt(1,2));

    Special_Taxi_Ctor(&st);

    Taxi_CCtor(&t2, &st);

    TaxiDisplay(t2);

    t2.virtuals[Dtor](&t2);

    ts1 = malloc(sizeof(Public_Convoy));

    Public_Convoy_Ctor(ts1);

    ts2 = malloc(sizeof(Public_Convoy));

    Public_Convoy_CCtor(ts2, ts1);

    ts1->virtuals[Display](ts1);

    ts2->virtuals[Display](ts2);

    ts1->virtuals[Dtor](ts1);

    free(ts1);
    /*display*/
    ts2->virtuals[Dtor](ts2);
    
    free(ts2);
    
    st.virtuals[Dtor](&st);
    
    for(i = 3; i >= 0; --i)
    {
        arr3[i].virtuals[Dtor](&arr3[i]);
    }
    m2.virtuals[Dtor](&m2);
    for(i = 2; i >= 0; --i)
    {
        arr2[i].virtuals[Dtor](&arr2[i]);
    }

    m.virtuals[Dtor](&m);/*all vals no need for v*/
}