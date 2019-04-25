// @FileNameData.h


#ifndef FILENAMEDATA_H_INCLUDED
#define FILENAMEDATA_H_INCLUDED

/*
* 基本的にファイルのパスはちょくちょく変わると思うので一括して管理しよう
* 他に良い方法があるかどうか(defineとかヘッダー管理について)は来週の田中先生に聞こう2/13
*/

#define Sample ""

//.obj ファイル

#define FILENAME_OBJ_TREE "Res/Object/Tree.obj"					//木
#define FILENAME_OBJ_HOUSE "Res/Object/House.obj"				//家
#define FILENAME_OBJ_ROCK "Res/Object/Rock.obj"					//岩
#define FILENAME_OBJ_GROUND "Res/Object/Ground.obj"				//床
#define FILENAME_OBJ_HUMAN "Res/Object/Human.obj"				//人間
#define FILENAME_OBJ_PLANE "Res/Object/Plane.obj"				//板
#define FILENAME_OBJ_BULLET "Res/Object/Bullet.obj"				//弾
#define FILENAME_OBJ_GROUNDTEST "Res/Object/GroundTest.obj"		//床のテスト
#define FILENAME_OBJ_TEST "Res/Object/Test.obj"					//なにか忘れた
#define FILENAME_OBJ_SKYBOX "Res/Object/SkyBox2.obj"			//なにか忘れた

#define FILENAME_OBJ_CART "Res/Object/Cart.obj"					//カートオブジェ

//.vert 頂点シェーダープログラム
#define FILENAME_SHADER_VERT_SIMPLE "Res/Shader/Simple.vert"						//
#define FILENAME_SHADER_VERT_FRAGMENTLIGHT "Res/Shader/FragmentLighting.vert"		//フォンシェーディング
#define FILENAME_SHADER_VERT_2DSPRITE "Res/Shader/2DSprite.vert" 					//スプライトで頂点をずらす用
#define FILENAME_SHADER_VERT_SPRITE "Res/Shader/Sprite.vert"						//
#define FILENAME_SHADER_VERT_VERTEXLIGHT "Res/Shader/VertexLighting.vert"			//
#define FILENAME_SHADER_VERT_FONT "Res/Shader/Font.vert"							//

//.frag フラグメントシェーダプログラム
#define FILENAME_SHADER_FRAG_SIMPLE "Res/Shader/Simple.frag"						//
#define FILENAME_SHADER_FRAG_FRAGMENTLIGHT "Res/Shader/FragmentLighting.frag"		//
#define FILENAME_SHADER_FRAG_2DSPRITE "Res/Shader/2DSprite.frag"					//
#define FILENAME_SHADER_FRAG_FONT "Res/Shader/Font.frag"							//
#define FILENAME_SHADER_FRAG_SPRITE "Res/Shader/Sprite.frag"						//
																					
//.tga テクスチャ画像
#define FILENAME_TGA_HOUSE "Res/Texture/House.tga"				//家
#define FILENAME_TGA_ROCK "Res/Texture/Rock.tga"				//岩
#define FILENAME_TGA_HUMAN "Res/Texture/Human.tga"				//人間
#define FILENAME_TGA_BULLET "Res/Texture/Bullet.tga"			//弾
#define FILENAME_TGA_STAGECLEAR "Res/Texture/StageClear.tga"	//2dステージクリアの
#define FILENAME_TGA_GAMEOVER "Res/Texture/GameOver.tga"		//2dゲームオーバー
#define FILENAME_TGA_HP "Res/Texture/HP.tga"					//2dヘルス
#define FILENAME_TGA_DAY "Res/Texture/Day.tga"					//2dしんっだ
#define FILENAME_TGA_SCORE "Res/Texture/Score.tga"				//2dスコア
#define FILENAME_TGA_FONT "Res/Font/Font.tga"					//フォント用テクスチャ
#define FILENAME_TGA_FONTDOT "Res/Font/FontDot.tga"				//新しいフォント.
#define FILENAME_TGA_NUMBERTEST "Res/Texture/Number_"			//ちょっとしたテスト
#define FILENAME_TGA_NUMBER0 "Res/Texture/Number_0.tga"			//
#define FILENAME_TGA_NUMBER1 "Res/Texture/Number_1.tga"			//
#define FILENAME_TGA_NUMBER2 "Res/Texture/Number_2.tga"			//
#define FILENAME_TGA_NUMBER3 "Res/Texture/Number_3.tga"			//
#define FILENAME_TGA_NUMBER4 "Res/Texture/Number_4.tga"			//
#define FILENAME_TGA_NUMBER5 "Res/Texture/Number_5.tga"			//
#define FILENAME_TGA_NUMBER6 "Res/Texture/Number_6.tga"			//
#define FILENAME_TGA_NUMBER7 "Res/Texture/Number_7.tga"			//
#define FILENAME_TGA_NUMBER8 "Res/Texture/Number_8.tga"			//
#define FILENAME_TGA_NUMBER9 "Res/Texture/Number_9.tga"			//
#define FILENAME_TGA_NUMBER10 "Res/Texture/Number_10.tga"			//
#define FILENAME_TGA_NUMBER20 "Res/Texture/Number_20.tga"			//
#define FILENAME_TGA_NUMBER30 "Res/Texture/Number_30.tga"			//
#define FILENAME_TGA_NUMBER40 "Res/Texture/Number_40.tga"			//
#define FILENAME_TGA_NUMBER50 "Res/Texture/Number_50.tga"			//
#define FILENAME_TGA_NUMBER60 "Res/Texture/Number_60.tga"			//
#define FILENAME_TGA_NUMBER70 "Res/Texture/Number_70.tga"			//
#define FILENAME_TGA_NUMBER80 "Res/Texture/Number_80.tga"			//
#define FILENAME_TGA_NUMBER90 "Res/Texture/Number_90.tga"			//
#define FILENAME_TGA_NUMBER100 "Res/Texture/Number_100.tga"			//
#define FILENAME_TGA_TEST "Res/Texture/Test.tga"				//なんだこれは
#define FILENAME_TGA_TITLEBACK "Res/Texture/TitleBack.tga"		//タイトルの背景
#define FILENAME_TGA_TITLELOGO "Res/Texture/TitleLogo.tga"		//タイトルのロゴ
#define FILENAME_TGA_CART "Res/Texture/Cart.tga"				//カート
#define FILENAME_TGA_SKYBOX "Res/Texture/SkyBox2.tga"				//背景
#define FILENAME_TGA_WHITE "Res/Texture/White.tga"				//白
#define FILENAME_TGA_RESULTFRAME "Res/Texture/TitleBack.tga"		//リザルトシーンの枠
#define FILENAME_TGA_RANWAY "Res/Texture/RanWay.tga"		//滑走路
#define FILENAME_TGA_MANUAL "Res/Texture/Manual.tga"			//マニュアル用テクスチャ
#define FILENAME_TGA_CREDIT "Res/Texture/Credit.tga"			//クレジット用テクスチャ.
#define FILENAME_TGA_TITLECREDIT "Res/Texture/TitleCredit.tga"			//クレジット用テクスチャ.
#define FILENAME_TGA_CART2D "Res/Texture/Cart2D.tga"			//クレジット用テクスチャ.


//wav 音声ファイル
#define FILENAME_WAV_MAINSCENE "Res/Audio/MainScene2.wav"		//本編
#define FILENAME_WAV_TITLESCENE "Res/Audio/TitleScene.wav"		//タイトル
#define FILENAME_WAV_RESULTSCENE "Res/Audio/ResultScene.wav"	//結果発表
#define FILENAME_WAV_DECISION "Res/Audio/SE_Decision.wav"		//決定王
#define FILENAME_WAV_CANCELL "Res/Audio/SE_Cancell.wav"			//キャンセル
#define FILENAME_WAV_PANELHIT "Res/Audio/SE_PanelHit.wav"		//パネルにぶつかった音
#define FILENAME_WAV_RADYGO "Res/Audio/SE_ReadyGo.wav"			//発進するとき
#define FILENAME_WAV_SELECT "Res/Audio/SE_Select.wav"			//セレクト画面
#define FILENAME_WAV_ROLLAR "Res/Audio/SE_Rollar.wav"			//フィールドで台車が走る音
#define FILENAME_WAV_RESULTCARVOICE "Res/Audio/SE_ResultCarVoice.wav"			//リザルトで車が走る音
#define FILENAME_WAV_EXPLOSION "Res/Audio/SE_Explosion.wav"			//タイトルで使おうかなと
#define FILENAME_WAV_RESULTBEGIN "Res/Audio/SE_ResultBegin.wav"			//リザルトに入った時

#endif // !FILENAMEDATA_H_INCLUDED
