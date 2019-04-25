//@file SelectManager.h


#ifndef SELECTMANAGER_H_INCLUDED
#define SELECTMANAGER_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "Audio.h"


/*
* タイトル等でよくあるモード選択などが複数階層ある場合に使うことを想定したクラス.
* 命名規則じゃないけれどstring型は 1_
*
*
*
*
*/
namespace Select {


	/*
	* 表示する選択肢の1つ分,
	* 選択先の情報を所持している.
	*
	*
	*/
	class Manager;
	class Unit{
	public:
		friend class Manager;
		void SetChoices(std::vector<std::string>);							//
		void SetNextUnit(std::string,Unit*);
		void SetFuncPtr(void(*func)());
	private:
		std::vector<std::string> string;			//表示する文字列ダニ
		std::map<std::string, Unit*> Choices;		//次の処理があればまた登録
		void(*funcPtr)() = nullptr;					//選択された時に何か処理したい場合は関数を登録する;

		unsigned int Hierarcht;						//ページの階層.
	};

	/*
	* Unitを統括するclass
	*
	*
	*
	*
	*
	*/
	class Manager {
	public:
		Manager();
		~Manager();

		void SetEntryPoint(Unit*);					//はじめに表示するエントリーポイントを登録
		void ProcessInput();						//入力処理.
		void Update();								//更新処理.
		void Render();								//描画処理.
		bool GetExit() const { return exitFlag; }	//ゲッター

		struct Layout {								//文字を描画するレイアウト(とりあえず回転は省くわ)
			glm::vec3 fTransform=glm::vec3(0);					//文字列の位置
			glm::vec3 fScale = glm::vec3(2);						//文字の大きさ
			float fLarge = 1.2f;										//肥大化の文字の拡大率
			glm::vec2 space=glm::vec2(30,30);						//フォントとフォントの間隔
		};

		Layout layout;								//迷った末public
		void Back();								//一つ戻る.
	private:
		Unit* entryPoint;							//はじめに表示するunit

		std::vector<Unit*> Trajectory;				//戻る(Exit)に対応するため Tranjectory/軌跡
		int selectNum = 0;
		void AddSelectNum(int);						//Numを足す処理.
		void Transision();							//遷移

		bool exitFlag = false;								//これ以上戻れない時
		//音
		Audio::EngineRef audio = Audio::Engine::Instance();
		Audio::SoundPtr decision;
		Audio::SoundPtr cancell;
		Audio::SoundPtr select;

	};

}//namespace Select


#endif // !SELECTMANAGER_H_INCLUDED
