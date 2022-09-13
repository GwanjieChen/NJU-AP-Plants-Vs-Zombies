/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.2
 *Email: 2117610943@qq.com
 */

#pragma once
#include "cocos2d.h"
#include "Based/Dialog.h"
#include "network/CCDownloader.h"

using namespace ui;
using namespace cocos2d;
using namespace cocos2d::experimental;

class UpdateClient :public Dialog
{
public:
    CREATE_FUNC(UpdateClient);

CC_CONSTRUCTOR_ACCESS:
    UpdateClient();
    virtual bool init();

private:
    enum class Update_Button
    {
        �ٶ���������,
        ��Ѷ΢������,
        ֱ������,
		�˳���Ϸ,
        ȷ��
    };
    void createDiglog();	                                                       /* �����Ի��� */
    void createButton(const std::string& name, Vec2& vec2, Update_Button button);  /* ������ť */
    void showText();
    void addScrollView();
    void addMouseEvent();
    void downloadHistoryText();
    void downloadData();
    void downloadProgress();
    void downloadSuccess();
    void downloadError();

private:
    Sprite* _dialog;    /* �Ի��� */
    std::unique_ptr<network::Downloader> _downloader;
    Label* _remindText;
    Label* _progressText;
    Label* _explanText;
    Label* _historyText;
    Sprite* _loadBarBackground;
    ui::LoadingBar* _loadingBar;
    ui::ScrollView* _textScrollView;
    bool _isNewDowndload;
};