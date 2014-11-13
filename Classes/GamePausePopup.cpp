//
//  GamePausePopup.cpp
//  DgDiary
//
//  Created by 사원3 on 2014. 11. 13..
//
//

#include "GamePausePopup.h"
#include "DataStorageHub.h"
#include "StarGoldData.h"
#include "KSLabelTTF.h"
#include "TouchSuctionLayer.h"
#include "CommonButton.h"
#include "CommonAnimation.h"
#include "MyLocalization.h"
#include "TitleRenewal.h"

GamePausePopup* GamePausePopup::create(int t_touch_priority, function<void()> t_end_func, function<void()> t_restart_func)
{
	GamePausePopup* t_mup = new GamePausePopup();
	t_mup->myInit(t_touch_priority, t_end_func, t_restart_func);
	t_mup->autorelease();
	return t_mup;
}

void GamePausePopup::myInit(int t_touch_priority, function<void()> t_end_func, function<void()> t_restart_func)
{
	is_menu_enable = false;
	
	touch_priority = t_touch_priority;
	end_func = t_end_func;
	restart_func = t_restart_func;
	
	gray = CCSprite::create("back_gray.png");
	gray->setOpacity(0);
	gray->setPosition(ccp(240,myDSH->ui_center_y));
	gray->setScaleX(1.f);
	gray->setScaleY(myDSH->ui_top/320);
	addChild(gray);
	
	suction = TouchSuctionLayer::create(touch_priority+1);
	addChild(suction);
	
	suction->setTouchEnabled(true);
	
	m_container = CCNode::create();
	m_container->setPosition(ccp(240,myDSH->ui_center_y));
	addChild(m_container);
	
	back_case = CCSprite::create("popup_large_back.png");
	back_case->setPosition(ccp(0,0));
	m_container->addChild(back_case);
	
	CCScale9Sprite* back_in = CCScale9Sprite::create("common_grayblue.png", CCRectMake(0, 0, 26, 26), CCRectMake(12, 12, 2, 2));
	back_in->setContentSize(CCSizeMake(251,135));
	back_in->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(0,10));
	back_case->addChild(back_in);
	
	KSLabelTTF* title_label = KSLabelTTF::create(myLoc->getLocalForKey(kMyLocalKey_pause), mySGD->getFont().c_str(), 12);
	title_label->disableOuterStroke();
	title_label->setAnchorPoint(ccp(0.5f,0.5f));
	title_label->setPosition(ccpFromSize(back_case->getContentSize()/2.f) + ccp(-85, back_case->getContentSize().height/2.f-35));
	back_case->addChild(title_label);
	
	CommonButton* close_button = CommonButton::createCloseButton(touch_priority);
	close_button->setPosition(ccp(back_case->getContentSize().width-25,back_case->getContentSize().height-22));
	close_button->setFunction([=](CCObject* sender)
							  {
								  if(!is_menu_enable)
									  return;
								  
								  is_menu_enable = false;
								  
								  AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								  
								  CommonAnimation::closePopup(this, m_container, gray, [=](){
									  
								  }, [=](){
									  end_func();
									  removeFromParent();
								  });
							  });
	back_case->addChild(close_button);
	
	
	{
		CCSprite* level1_back = CCSprite::create("stop_level.png");
		level1_back->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(-62,33));
		back_in->addChild(level1_back);
		
		KSLabelTTF* grade_label = KSLabelTTF::create("초급", mySGD->getFont().c_str(), 13);
		grade_label->enableOuterStroke(ccBLACK, 1, 255, true);
		grade_label->setPosition(ccp(38,41));
		level1_back->addChild(grade_label);
		
		KSLabelTTF* cell_count_label = KSLabelTTF::create("3x4", mySGD->getFont().c_str(), 18);
		cell_count_label->setGradientColor(ccc4(255, 115, 250, 255), ccc4(215, 60, 130, 255), ccp(0,-1));
		cell_count_label->enableOuterStroke(ccBLACK, 1, 255, true);
		cell_count_label->setPosition(ccp(38,21));
		level1_back->addChild(cell_count_label);
		
		KSLabelTTF* reward_label = KSLabelTTF::create("보상", mySGD->getFont().c_str(), 12);
		reward_label->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_label->setPosition(ccp(90,42));
		level1_back->addChild(reward_label);
		
		KSLabelTTF* reward_count = KSLabelTTF::create("+1", mySGD->getFont().c_str(), 13);
		reward_count->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_count->setAnchorPoint(ccp(0,0.5f));
		reward_count->setPosition(ccp(90,21));
		level1_back->addChild(reward_count);
	}
	
	{
		CCSprite* level2_back = CCSprite::create("stop_level.png");
		level2_back->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(62,33));
		back_in->addChild(level2_back);
		
		KSLabelTTF* grade_label = KSLabelTTF::create("중급", mySGD->getFont().c_str(), 13);
		grade_label->enableOuterStroke(ccBLACK, 1, 255, true);
		grade_label->setPosition(ccp(38,41));
		level2_back->addChild(grade_label);
		
		KSLabelTTF* cell_count_label = KSLabelTTF::create("4x5", mySGD->getFont().c_str(), 18);
		cell_count_label->setGradientColor(ccc4(255, 115, 250, 255), ccc4(215, 60, 130, 255), ccp(0,-1));
		cell_count_label->enableOuterStroke(ccBLACK, 1, 255, true);
		cell_count_label->setPosition(ccp(38,21));
		level2_back->addChild(cell_count_label);
		
		KSLabelTTF* reward_label = KSLabelTTF::create("보상", mySGD->getFont().c_str(), 12);
		reward_label->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_label->setPosition(ccp(90,42));
		level2_back->addChild(reward_label);
		
		KSLabelTTF* reward_count = KSLabelTTF::create("+2", mySGD->getFont().c_str(), 13);
		reward_count->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_count->setAnchorPoint(ccp(0,0.5f));
		reward_count->setPosition(ccp(90,21));
		level2_back->addChild(reward_count);
	}
	
	{
		CCSprite* level3_back = CCSprite::create("stop_level.png");
		level3_back->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(-62,-33));
		back_in->addChild(level3_back);
		
		KSLabelTTF* grade_label = KSLabelTTF::create("고급", mySGD->getFont().c_str(), 13);
		grade_label->enableOuterStroke(ccBLACK, 1, 255, true);
		grade_label->setPosition(ccp(38,41));
		level3_back->addChild(grade_label);
		
		KSLabelTTF* cell_count_label = KSLabelTTF::create("5x7", mySGD->getFont().c_str(), 18);
		cell_count_label->setGradientColor(ccc4(255, 115, 250, 255), ccc4(215, 60, 130, 255), ccp(0,-1));
		cell_count_label->enableOuterStroke(ccBLACK, 1, 255, true);
		cell_count_label->setPosition(ccp(38,21));
		level3_back->addChild(cell_count_label);
		
		KSLabelTTF* reward_label = KSLabelTTF::create("보상", mySGD->getFont().c_str(), 12);
		reward_label->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_label->setPosition(ccp(90,42));
		level3_back->addChild(reward_label);
		
		KSLabelTTF* reward_count = KSLabelTTF::create("+3", mySGD->getFont().c_str(), 13);
		reward_count->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_count->setAnchorPoint(ccp(0,0.5f));
		reward_count->setPosition(ccp(90,21));
		level3_back->addChild(reward_count);
	}
	
	{
		CCSprite* level4_back = CCSprite::create("stop_level.png");
		level4_back->setPosition(ccpFromSize(back_in->getContentSize()/2.f) + ccp(62,-33));
		back_in->addChild(level4_back);
		
		KSLabelTTF* grade_label = KSLabelTTF::create("최고급", mySGD->getFont().c_str(), 13);
		grade_label->enableOuterStroke(ccBLACK, 1, 255, true);
		grade_label->setPosition(ccp(38,41));
		level4_back->addChild(grade_label);
		
		KSLabelTTF* cell_count_label = KSLabelTTF::create("6x8", mySGD->getFont().c_str(), 18);
		cell_count_label->setGradientColor(ccc4(255, 115, 250, 255), ccc4(215, 60, 130, 255), ccp(0,-1));
		cell_count_label->enableOuterStroke(ccBLACK, 1, 255, true);
		cell_count_label->setPosition(ccp(38,21));
		level4_back->addChild(cell_count_label);
		
		KSLabelTTF* reward_label = KSLabelTTF::create("보상", mySGD->getFont().c_str(), 12);
		reward_label->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_label->setPosition(ccp(90,42));
		level4_back->addChild(reward_label);
		
		KSLabelTTF* reward_count = KSLabelTTF::create("+4", mySGD->getFont().c_str(), 13);
		reward_count->enableOuterStroke(ccBLACK, 1, 255, true);
		reward_count->setAnchorPoint(ccp(0,0.5f));
		reward_count->setPosition(ccp(90,21));
		level4_back->addChild(reward_count);
	}
	
	
	CommonButton* main_button = CommonButton::create(myLoc->getLocalForKey(kMyLocalKey_toMain), 13, CCSizeMake(86,46), CCScale9Sprite::create("subapp_bt.png", CCRectMake(0,0,86,46), CCRectMake(42, 22, 2, 2)), -999);
	main_button->setFunction([=](CCObject* sender)
							 {
								 if(!is_menu_enable)
									 return;
								 
								 is_menu_enable = false;
								 
								 AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								 
								 CCDirector::sharedDirector()->replaceScene(TitleRenewalScene::scene());
							 });
	main_button->setPosition(ccp(back_case->getContentSize().width/2.f-87, 47));
	back_case->addChild(main_button);
	
	CommonButton* replay_button = CommonButton::create(myLoc->getLocalForKey(kMyLocalKey_ingameReplay), 13, CCSizeMake(86,46), CCScale9Sprite::create("subapp_bt.png", CCRectMake(0,0,86,46), CCRectMake(42, 22, 2, 2)), -999);
	replay_button->setFunction([=](CCObject* sender)
							 {
								 if(!is_menu_enable)
									 return;
								 
								 is_menu_enable = false;
								 
								 AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								 
								 CommonAnimation::closePopup(this, m_container, gray, [=](){
									 
								 }, [=](){
									 restart_func();
									 removeFromParent();
								 });
							 });
	replay_button->setPosition(ccp(back_case->getContentSize().width/2.f, 47));
	back_case->addChild(replay_button);
	
	CommonButton* resume_button = CommonButton::create(myLoc->getLocalForKey(kMyLocalKey_continue), 13, CCSizeMake(86,46), CCScale9Sprite::create("subapp_bt.png", CCRectMake(0,0,86,46), CCRectMake(42, 22, 2, 2)), -999);
	resume_button->setFunction([=](CCObject* sender)
							   {
								   if(!is_menu_enable)
									   return;
								   
								   is_menu_enable = false;
								   
								   AudioEngine::sharedInstance()->playEffect("se_button1.mp3", false);
								   
								   CommonAnimation::closePopup(this, m_container, gray, [=](){
									   
								   }, [=](){
									   end_func();
									   removeFromParent();
								   });
							   });
	resume_button->setPosition(ccp(back_case->getContentSize().width/2.f+87, 47));
	back_case->addChild(resume_button);
	
	
	CommonAnimation::openPopup(this, m_container, gray, [=](){
	}, [=](){
		is_menu_enable = true;
	});
}

