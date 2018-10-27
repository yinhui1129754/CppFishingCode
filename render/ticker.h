#pragma once
class DemoApp;
class ticker
{
public:
	ticker();
	~ticker();
	void start();
	void stop();
	void setTimmer(float timmer);
	void addFun(void(*fs)(DemoApp ** app, ticker *tk));
	void render(DemoApp ** app);
	void setId(string str);
public:
	float timmer = 0;
	double msTime = 0;
	int fps = 0;
	int fpsInt = 0;
	double oldTimmer =0; 
	double newTimmer=0;
	double fpsTimmer=0;
	string id = "";
private :
	vector <void(*)(DemoApp ** app, ticker *tk)> tickerArr;
	bool started =false;

};

