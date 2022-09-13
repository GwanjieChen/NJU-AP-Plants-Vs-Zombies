#include "Based/GlobalVariable.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

Global* Global::_instance = nullptr;

Global* Global::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)Global;
	}
	return _instance;
}

Global::Global() :
  prohibitId(-1)
, _sumAnimationInterval(0)
, _frequence(0)
, userInformation(new UserInformation())
{
}

Global::~Global()
{
	if(userInformation)delete userInformation;
}

void Global::resumeProhibit()
{
	AudioEngine::setFinishCallback(prohibitId, [=](int i, string name)
		{
			prohibitId = -1;
		});
}

void Global::checkAnimationInterval()
{
	++_frequence;
	if (_sumAnimationInterval <= 0)
	{
		_sumAnimationInterval = 1.f / Director::getInstance()->getSecondsPerFrame();
	}
	else
	{
		_sumAnimationInterval = (_sumAnimationInterval + 1.f / Director::getInstance()->getSecondsPerFrame()) / 2;
	}

	if (_sumAnimationInterval <= 20 && _frequence > 60)
	{
		AudioEngine::stopAll();
		wstring str = L"        �ܱ�Ǹ����⵽�������е�ƽ��֡��̫�Ͷ���Ϸ�Ŀ������м����Ӱ�졣\
��������ȷ����ť�رմ���Ϸ���رղ�ʹ�õ������������������Ӳ�����õȲ������ٴγ������д���Ϸ��";

		if (MessageBoxW(Director::getInstance()->getOpenGLView()->getWin32Window(), str.c_str(), L"��Ϸƽ��֡��̫��(ƽ��FPS <= 20FPS)", MB_ICONERROR | MB_OK) == MB_OKCANCEL)
		{
			Director::getInstance()->end();
		}
	}
}

