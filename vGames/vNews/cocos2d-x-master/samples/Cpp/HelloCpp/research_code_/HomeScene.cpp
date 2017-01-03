//
//  HomeScene.cpp
//  EinsteinPrototype
//
//  Created by Marco Rossi on 2/6/13.
//  Copyright (c) 2013 Farofa Studios. All rights reserved.
//

#include "HomeScene.h"

#include "cocos2d.h"
USING_NS_CC;

 
HomeScene::HomeScene()
{
 
    InitHome();
}

void HomeScene::InitHome()
{
    IFixedMenu::initFixedMenu(INICIO);
    CCMenu* options = CCMenu::create();
    
	CCSprite* logo = CCSprite::create("bg_new.png");
	logo->setAnchorPoint(ccp(0, 0));
	logo->setPosition(ccp(0, 0));
    
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    //Cria os menus que ficam no meio da tela ( como chegar, banheiros, especialidades e etc) 
    createMenuItem(options, COMO_CHEGAR, "comochegar_new.png", "comochegar_new_hover.png", 20, winsize.height - 186, menu_selector(HomeScene::FixedMenuCallBack), this);
    
	createMenuItem(options, ESPECIALIDADES_MEDICAS, "especialidades_new.png", "especialidade_new_hover.png",winsize.width/2 - 35, winsize.height - 126, menu_selector(HomeScene::FixedMenuCallBack), this);
    
	createMenuItem(options, SERVICOS, "servicos_new.png", "servicos_new_hover.png",winsize.width - 20 - 70, winsize.height - 186, menu_selector(HomeScene::FixedMenuCallBack), this);
	
	createMenuItem(options, BANHEIROS, "sanitarios_new.png", "sanitarios_new_hover.png", 20, 170, menu_selector(HomeScene::FixedMenuCallBack), this);
    
	createMenuItem(options, ESTACIOMENTOS, "estacionamento_new.png", "estacionamento_new_hover.png",winsize.width/2 - 35, 90, menu_selector(HomeScene::FixedMenuCallBack), this);
    
    createMenuItem(options, INFORMACOES, "informacoes_new.png", "informacoes_new_hover.png",winsize.width - 20 - 70, 170, menu_selector(HomeScene::FixedMenuCallBack), this);

    options->setAnchorPoint(ccp(0, 0));
	options->setPosition(ccp(0, 0)); 
    
    CCSprite* welcome = CCSprite::create("BemVindo.png");
	welcome->setAnchorPoint(ccp(0, 0));
	welcome->setPosition(ccp(0, welcome->boundingBox().size.height -10));

    CCLayerColor* container = CCLayerColor::create(ccc4(255,255,255,255));
    container->addChild(welcome);
	container->addChild(logo);
    container->addChild(options);
    this->addChild(container);
}

/*******************************************************************************************************************************/
/* IFixedMenu                                     
   Menu com nenhum item selecionado ( padrao) 
 */
/*******************************************************************************************************************************/
void IFixedMenu::initFixedMenu(){
    initFixedMenu(NONE);
}



//Ajusta os botoes deixa um selecionado desabilitado e o resto habilitado é recriado ao clicar nos itens
//´E o painel com os botões mapas, inicio, procurar na parte inferior da tela
void IFixedMenu::initFixedMenu(HomeMenuState newState)
{
    CCMenu* oFixedMenu = CCMenu::create();
    oFixedMenu->setAnchorPoint(ccp(0, 0));
	oFixedMenu->setPosition(ccp(0, 0));

    switch(newState)
    {
        case INICIO:
            createMenuItem(oFixedMenu, INICIO, "FooterInicio_press.png", "FooterInicio_press.png",0, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MINHAS_ROTAS, "FooterMinhasRotas_btn.png", "FooterMinhasRotas_press.png",162, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MAPAS, "FooterMapas_btn.png", "FooterMapas_press.png",81, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, PROCURAR, "FooterProcurar_btn.png", "FooterProcurar_press.png",243, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            break;
        case MINHAS_ROTAS:
            createMenuItem(oFixedMenu, INICIO, "FooterInicio_btn.png", "FooterInicio_press.png",0, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MINHAS_ROTAS, "FooterMinhasRotas_press.png", "FooterMinhasRotas_press.png",162, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MAPAS, "FooterMapas_btn.png", "FooterMapas_press.png",81, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, PROCURAR, "FooterProcurar_btn.png", "FooterProcurar_press.png",243, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            break;
        case MAPAS:
            createMenuItem(oFixedMenu, INICIO, "FooterInicio_btn.png", "FooterInicio_press.png",0, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MINHAS_ROTAS, "FooterMinhasRotas_btn.png", "FooterMinhasRotas_press.png",162, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MAPAS, "FooterMapas_press.png", "FooterMapas_press.png",81, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, PROCURAR, "FooterProcurar_btn.png", "FooterProcurar_press.png",243, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            break;
        case PROCURAR:
            createMenuItem(oFixedMenu, INICIO, "FooterInicio_btn.png", "FooterInicio_press.png",0, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MINHAS_ROTAS, "FooterMinhasRotas_btn.png", "FooterMinhasRotas_press.png",162, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MAPAS, "FooterMapas_btn.png", "FooterMapas_press.png",81, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, PROCURAR, "FooterProcurar_press.png", "FooterProcurar_press.png",243, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            break;
        case NONE:
            createMenuItem(oFixedMenu, INICIO, "FooterInicio_btn.png", "FooterInicio_press.png",0, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MAPAS, "FooterMapas_btn.png", "FooterMapas_press.png",81, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, MINHAS_ROTAS, "FooterMinhasRotas_btn.png", "FooterMinhasRotas_press.png",162, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            createMenuItem(oFixedMenu, PROCURAR, "FooterProcurar_btn.png", "FooterProcurar_press.png",243, 0, menu_selector(HomeScene::FixedMenuCallBack), this);
            break;
        default:
            throw "";
            break;
    }
    this->addChild(oFixedMenu,2,0);
}

//  Created by Marco Rossi on 2/6/13.
//  Copyright (c) 2013 Farofa Studios. All rights reserved.
void IFixedMenu::FixedMenuCallBack(CCObject *sender)
{
//    if( LayerWebView::isKeyBoardVisible())
//        return;
  
   CCApplication::sharedApplication()->hideBars(false);
   if(AlertViewScene::isActive )
        return;
    CCLayer* newNode =  NULL;
//    LayerWebView::forceRelease();
    switch (((CCNode*)sender)->getTag())
    {
        case MINHAS_ROTAS:
            newNode =  new MinhasRotasScene();
            break;
//        case ESTACIOMENTOS:
//            newNode = new ParkingScene();
//            break;
        case PROCURAR:
            newNode = new SearchScene();
            break;
//        case BANHEIROS:
//            newNode = new BathRoomScene();
//            break;
//        case INICIO:
//            CCApplication::sharedApplication().hideBars(false);
//            newNode =  new HomeScene();
//            break;
//        default:
//            newNode = new HowToGoScene((HomeMenuState)((CCNode*)sender)->getTag());
//            break;
    }
    if( newNode != NULL)
        changeScene(newNode);
}

HomeScene::~HomeScene()
{
    
}