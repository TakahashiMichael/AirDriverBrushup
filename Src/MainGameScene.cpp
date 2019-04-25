/**
* @file MainGameScene.cpp
*/
#include "MainGameScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include "FileNameData.h"
#include "ResultScene.h"



/**
* ������.
*/
bool MainGameScene::Initialize()
{
	random.seed(std::random_device()());
	//std::uniform_int_distribution<int> testnum(0,10);
	//std::cout << "�f�o�b�O:�����_���̒l��\��"<<testnum(random) << std::endl;
	//int numtest[10];
	//for (int i = 0; i < 10; ++i) {
	//	numtest[i] = testnum(random);

	//	std::cout << "�f�o�b�O:�����_���̒l��\��" << numtest[i] << std::endl;
	//}
	std::vector<std::string> modelFiles;
	modelFiles.push_back(FILENAME_OBJ_TREE);
	modelFiles.push_back(FILENAME_OBJ_HOUSE);
	modelFiles.push_back(FILENAME_OBJ_ROCK);
	modelFiles.push_back(FILENAME_OBJ_GROUND);
	modelFiles.push_back(FILENAME_OBJ_CART);
	modelFiles.push_back(FILENAME_OBJ_PLANE);
	modelFiles.push_back(FILENAME_OBJ_BULLET);
	modelFiles.push_back(FILENAME_OBJ_GROUNDTEST);
	modelFiles.push_back(FILENAME_OBJ_SKYBOX);
	if (!meshList.Allocate(modelFiles)) {
		return false;
	}

	progSimple.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_SIMPLE, FILENAME_SHADER_FRAG_SIMPLE));
	progLighting.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_FRAGMENTLIGHT, FILENAME_SHADER_FRAG_FRAGMENTLIGHT));


	//�_�����z�̐ݒ�.�킩��₷���悤�Ɉ�x�z��Œ�`���Ă݂�
	int nums[50] =
	{
		100,70,70,50,50,50,40,40,40,40,
		30,30,30,30,30,20,20,20,20,20,
		10,10,10,10,10,10,10,10,10,10,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
	};
	//���蓖�Ă̏���.
	for (int i = 0; i < panelCountAll; ++i) {
		pointList.push_back(nums[i]);
	}
	//�V���b�t�����鏈��.
	std::uniform_int_distribution<int> suffixram(0, panelCountAll - 1);
	for (int i = 0; i < panelCountAll; ++i) {

		const int suffix = suffixram(random);
		int tmp = pointList[i];
		pointList[i] = pointList[suffix];
		pointList[suffix] = tmp;
	}



	// �e�N�X�`�����쐬����.
	const int imageWidth = 8; // �摜�̕�.
	const int imageHeight = 8; // �摜�̍���.
	const GLuint B = 0xff'40'40'40; // ��.
	const GLuint W = 0xff'ff'ff'ff; // ��.
	const GLuint imageData[imageWidth * imageHeight] = {
	  W, W, B, W, W, W, W, W,
	  W, W, B, W, W, W, W, W,
	  W, W, B, W, W, W, W, W,
	  B, B, B, B, B, B, B, B,
	  W, W, W, W, W, W, B, W,
	  W, W, W, W, W, W, B, W,
	  W, W, W, W, W, W, B, W,
	  B, B, B, B, B, B, B, B,
	};
	const GLuint G2 = 0xff'10'80'20;
	const GLuint G1 = 0xff'20'C0'40;
	const GLuint G0 = 0xff'40'E0'80;
	const GLuint R0 = 0xff'20'60'A0;
	const GLuint R1 = 0xff'10'20'60;
	const GLuint imageTree[imageWidth * imageHeight] = {
	  R0,R1,R0,R1,R0,R1,R0,R1,
	  R0,R0,R0,R0,R0,R0,R0,R0,
	  G2,G1,G2,G1,G2,G1,G2,G1,
	  G1,G2,G1,G2,G1,G2,G1,G2,
	  G1,G1,G2,G1,G1,G1,G2,G1,
	  G0,G1,G0,G1,G0,G1,G0,G1,
	  G1,G0,G1,G0,G1,G0,G1,G0,
	  G0,G0,G0,G0,G0,G0,G0,G0,
	};
	texId.Reset(Texture::CreateImage2D(imageWidth, imageHeight, imageData, GL_RGBA, GL_UNSIGNED_BYTE));
	texTree.Reset(Texture::CreateImage2D(imageWidth, imageHeight, imageTree, GL_RGBA, GL_UNSIGNED_BYTE));
	texHouse.Reset(Texture::LoadImage2D(FILENAME_TGA_HOUSE));
	texRanWay.Reset(Texture::LoadImage2D(FILENAME_TGA_RANWAY));
	texRock.Reset(Texture::LoadImage2D(FILENAME_TGA_ROCK));
	texHuman.Reset(Texture::LoadImage2D(FILENAME_TGA_CART));
	texBullet.Reset(Texture::LoadImage2D(FILENAME_TGA_BULLET));
	texSkyBox.Reset(Texture::LoadImage2D(FILENAME_TGA_SKYBOX));



	//�_�̃e�N�X�`���[���擾����.
	for (int i = 0; i < 11; ++i) {
		int num = i * 10;
		std::string filename(FILENAME_TGA_NUMBERTEST);
		std::string extension(".tga");
		if (i == 10) {
			filename += "100";
		}
		else {
			filename += '0' + i;
			if (i != 0) {
				filename += '0';
			}
		}
		filename += extension;
		texNums.insert(std::make_pair(num , Texture::LoadImage2D(filename.c_str())));
	}

	texFont.Reset(Texture::LoadImage2D(FILENAME_TGA_FONTDOT));
	//for (int i = 0; i < 10; ++i) {
	//	std::string filename = "Res/Number_";
	//	filename += '0' + i;
	//	filename += ".tga";
	//	texNumber[i].Reset(Texture::LoadImage2D(filename.c_str()));
	//}

	// ���C�g�̐ݒ�.
	lights.ambient.color = glm::vec3(0.05f, 0.1f, 0.1f);
	lights.directional.direction = glm::normalize(glm::vec3(5, -2, -2));
	lights.directional.color = glm::vec3(0.8f,0.6f,0.4f);
	lights.point.position[0] = glm::vec3(5, 4, 0);
	lights.point.color[0] = glm::vec3(1.0f, 0.8f, 0.4f)*50.0f;

	lights.spot.posAndInnerCutOff[0] = glm::vec4(-6, 6, 8, std::cos(glm::radians(15.0f)));
	lights.spot.dirAndCutOff[0] = glm::vec4(glm::normalize(glm::vec3(-1, -2, -2)), std::cos(glm::radians(20.0f)));
	lights.spot.color[0] = glm::vec3(0.4f, 0.8f, 1.0f) * 200.0f;


	pointLightAngle = 0;

	player.Initialize(4, texHuman.Get(), 10, playerStartPos, glm::vec3(0,180,0), glm::vec3(1));
	player.colLocal = { {-0.5f, 0, -0.5f }, {1, 1.7f, 1} };
	player.direction = 180;
	playerBulletList.resize(128);
	for (auto& e : playerBulletList) {
		e = new BulletActor;
	}

	enemyList.resize(128);
	for (auto& e : enemyList) {
		e = new ZombieActor;
	}

	objectList.resize(128);
	for (auto& e : objectList) {
		e = new Actor;
	}

	frontPanelList.resize(frontPanelAll);
	for (auto& e : frontPanelList) {
		e = new Actor;
	}
	footPanelList.resize(footPanelAll);
	for (auto& e : footPanelList) {
		e = new Actor;
	}


	
	objectList[0]->Initialize(5, texRanWay.Get(), 1, ranwayOrigin, glm::vec3(glm::radians(-90.0f), 0, 0), glm::vec3(ranwaySize.x / 2, ranwaySize.z / 2, 1));
	objectList[0]->Update(0);

	SkyBox.Initialize(8, texSkyBox.Get(), 1,glm::vec3(0), glm::vec3(0), glm::vec3(500));


	//�p�l���̏������t�����g
	for (int i = 0; i < frontPanelList.size(); ++i) {
		int width = i % frontWidthCount;
		int heigth = i / frontWidthCount;
		frontPanelList[i]->Initialize(5, texNums[pointList[i]].Get(), 1, glm::vec3(frontOnePanel.x * width+frontOnePanel.x/2, frontOnePanel.y * heigth+frontOnePanel.y/2, 0), glm::vec3(0), glm::vec3(frontOnePanel.x/2, frontOnePanel.y/2, 1));
		frontPanelList[i]->Update(0);
	}	//�p�l���̏������t�b�g
	for (int i = 0; i < footPanelList.size(); ++i) {
		int width = i % footWidthCount;
		int heigth = i / footWidthCount;
		footPanelList[i]->Initialize(5, texNums[pointList[i+frontPanelList.size()]].Get(), 1, glm::vec3(footOnePanel.x * width + footOnePanel.x / 2, 0, footOnePanel.y * heigth + footOnePanel.y / 2), glm::vec3(glm::radians(-90.0f),0,0), glm::vec3(footOnePanel.x / 2, footOnePanel.y / 2, 1));
		footPanelList[i]->Update(0);
	}
	//glm::vec3 Test1(10,10,10);
	//glm::vec3 Test2(2,2,2);
	//std::cout << "x:"<<Test1.x<<" y:"<<Test1.y<<" z:"<<Test1.z<<std::endl;
	//Test1 /= Test2;

	//std::cout << "x:" << Test1.x << " y:" << Test1.y << " z:" << Test1.z << std::endl;


	std::cout << meshList.tmpIndices.size() << std::endl;;
	std::cout << meshList.tmpVertices.size() << std::endl;;
	groundGrid.Initialize();
	groundGrid.SetPolyList();
	groundGrid.SearchGrid();





	//BGM��炷
	backBGM = audio.Prepare(FILENAME_WAV_MAINSCENE);
	SEpanelHit = audio.Prepare(FILENAME_WAV_PANELHIT);
	SEradyGo = audio.Prepare(FILENAME_WAV_RADYGO);
	backBGM->Play(Audio::Flag::Flag_Loop);


	//sprite�̏�����.
	sprTest = Sprite2D(FILENAME_TGA_WHITE);


	//camera�̏�����
	camera = Camera(&cameraTarget,10.0f);


	//�G���A�̐ݒ�
	playerArea = Area::RanWay;
	player.stop = true;

	//
	state = State::StandBy;

	//�z���C�g�̐F��ݒ肵�ăX�v���C�g�ɓo�^���Ă���
	whiteOut = glm::vec4(1);
	sprTest.SetColor(&whiteOut);

	//�n�܂钼�O�ɖ炷
	SEradyGo->Play();



	return true;


}

/**
* ���͔��f.
*/
void MainGameScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	{
		player.velocity.x = player.velocity.z = 0;

	}
	if (window.IsKeyDown(GLFW_KEY_ENTER)) {
		NextScene("Result");
	}


	//�f�o�b�O�p�J�����ړ�
	if (window.IsKeyPressed(GLFW_KEY_UP)) {
		cameraTarget+= camera.normalXZ();
	}
	else if (window.IsKeyPressed(GLFW_KEY_DOWN)) {

	}
	if (window.IsKeyPressed(GLFW_KEY_RIGHT)) {

	}
	else if (window.IsKeyPressed(GLFW_KEY_LEFT)) {

	}
	if (window.IsKeyPressed(GLFW_KEY_A)) {
		camera.normalRotateY(1.0f);
	}
	else if (window.IsKeyPressed(GLFW_KEY_D)) {
		camera.normalRotateY(-1.0f);

	}
	if (window.IsKeyPressed(GLFW_KEY_W)) {
		camera.normalRotateX(1.0f);
	}
	else if (window.IsKeyPressed(GLFW_KEY_S)) {
		camera.normalRotateX(-1.0f);

	}




	player.ProcessInput();
}

/**
* ��ԍX�V.
*/
void MainGameScene::Update()
{
	const float deltaTime = (float)GLFWEW::Window::Instance().DeltaTime();


	if (state == State::StandBy) {
		StandBy();
	}



	//�e�X�g.���C�g�I�u�W�F�N�g���v���C���[�̏��.
	lights.point.position[0] = player.position + glm::vec3(0, 5, 0);



	// �Q�[���̖ړI:
	// - �����ɗN���Ă���]���r��|��������.
	// - �K�萔��|���ƃX�e�[�W�N���A.
	// - �X�e�[�W���ƂɌ��߂�ꂽ���̃]���r��|���ƃN���A.
	// - �X�e�[�W���i�ނƏo������]���r�̑����A�����������������A�ړ����x���オ��.
	// - �v���C���[�̗̑͂�0�ȉ��ɂȂ�����Q�[���I�[�o�[.

	// �]���r�̓���:
	// - �}�b�v��10m�l���ɋ�؂�A���̒��̃����_���ɑI�΂ꂽ���ɏo��.
	// - (�X�e�[�W��*2+0�`3)�̂��܂Ƃ܂��ďo������.
	// - �o���Ԋu��(30-�X�e�[�W��*2)�b. ������10�b�����ɂ͂Ȃ�Ȃ�.
	// - �o����̓v���C���[��ǂ�������.
	// - �v���C���[�ɋ߂Â��ƁA�����̐��ʂɒ���I�ɍU������𔭐�������.
	// - �U�������1�t���[������.
	// - �U����������ƃv���C���[�̓_���[�W�𕉂�.

	// �v���C���[�̍X�V.
	//player.setvNormal(camera.normalXZ());
	player.Update(deltaTime);
	for (auto& object : objectList) {
		if (object->health > 0) {
			if (DetectCollision(player, *object)) {
				const CollisionTime t = FindCollisionTime(*object, player, deltaTime);
				if (t.plane != CollisionPlane::none) {
					const float time = deltaTime * t.time - 0.00001f;
					player.position += player.velocity * time;
					if (t.plane == CollisionPlane::negativeX || t.plane == CollisionPlane::positiveX) {
						player.velocity.x = 0;
					}
					else if (t.plane == CollisionPlane::negativeY || t.plane == CollisionPlane::positiveY) {
						player.velocity.y = 0;
					}
					else if (t.plane == CollisionPlane::negativeZ || t.plane == CollisionPlane::positiveZ) {
						player.velocity.z = 0;
					}
					player.velocity *= -t.time;
					player.position += player.velocity * -time;
				}
			}
		}
	}
	////�v���C���[�ƍ�̔���.
	//if (groundGrid.GroundFunc(player.position, 1.0f))
	//{
	//	if (player.GetMoveform() != PlayerActor::Moveform_brake) {
	//		player.setMoveform(PlayerActor::Moveform_Straight);
	//	}

	//}
	////���̎d�l�����ꂽ���̂Ńv���C���[��y���W��0�𒴂��Ȃ��悤�ɐݒ�.
	//else if (player.position.y < 0) {
	//	player.position.y = 0;
	//	if ( player.GetMoveform() != PlayerActor::Moveform_brake) {
	//		player.setMoveform(PlayerActor::Moveform_Straight);
	//	}
	//}
	//else {
	//	if (player.GetMoveform() != PlayerActor::Moveform_AirBrake) {
	//		player.setMoveform(PlayerActor::Moveform_Air);
	//	}
	//}

	// ���@�V���b�g�̍X�V.
	UpdateActorList(playerBulletList, deltaTime);

	// �p�l���̍X�V
	UpdateActorList(frontPanelList, deltaTime);
	UpdateActorList(footPanelList, deltaTime);

	// �]���r�̍X�V.
	UpdateActorList(enemyList, deltaTime);






	// �������f����Y����]�p���X�V.
	pointLightAngle += glm::radians(90.0f) * deltaTime;
	if (pointLightAngle > glm::radians(360.0f)) {
		pointLightAngle -= glm::radians(360.0f);
	}

	//
	StayPanel();

	//�v���C���[���͈͊O�ɏo���Ƃ��Ƀ|�W�V�������C������
	ControlPos();
	
	//�v���C���[���|�C���g�p�l���Ƀq�b�g�������ǂ����𒲂ׂď�������
	HitPanel();

	SkyBox.position = player.position;

}

/**
* �`��.
*/
void MainGameScene::Render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�f�o�b�O

	// ���W�ϊ��s����쐬����
	const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
	const glm::mat4x4 matView = glm::lookAt(player.CameraPos(), player.CameraTarPos(), glm::vec3(0, 1, 0));
	//const glm::mat4x4 matView = glm::lookAt(camera.GetPos(),cameraTarget , glm::vec3(0, 1, 0));
	progLighting.SetViewProjectionMatrix(matProj * matView);
	progSimple.SetViewProjectionMatrix(matProj * matView);

	progLighting.Use();

	meshList.BindVertexArray();

	// ������ݒ肷��.
	progLighting.SetLightList(lights);

	progLighting.BindTexture(0, player.texture);
	progLighting.Draw(meshList[player.mesh], player.position, player.rotation, player.scale);

	RenderActorList(objectList, progLighting, meshList);
	RenderActorList(enemyList, progLighting, meshList);
	RenderActorList(playerBulletList, progLighting, meshList);
	RenderActorList(frontPanelList, progLighting, meshList);
	RenderActorList(footPanelList, progLighting, meshList);
	//progLighting.BindTexture(0, SkyBox.texture);
	//progLighting.Draw(meshList[SkyBox.mesh], SkyBox.position, SkyBox.rotation, SkyBox.scale);

	// �|�C���g�E���C�g�̈ʒu��������悤�ɓK���ȃ��f����\��.
	progSimple.Use();
	progSimple.BindTexture(0,SkyBox.texture);
	progSimple.Draw(meshList[SkyBox.mesh], SkyBox.position, SkyBox.rotation, SkyBox.scale);
	//void RenderActorList(std::vector<Actor*>& actorList, Shader::Program& shader, MeshList& meshList)
	//{
	//	for (auto& actor : actorList) {
	//		if (actor && actor->health > 0) {
	//			shader.BindTexture(0, actor->texture);
	//			shader.Draw(meshList[actor->mesh], actor->position, actor->rotation, actor->scale);
	//		}
	//	}

	//progSimple.BindTexture(0, texId.Get());
	//for (int i = 0; i < 8; ++i) {
	//	progSimple.Draw(meshList[4], lights.point.position[i], glm::vec3(0, pointLightAngle, 0), glm::vec3(1.0f, -0.25f, 1.0f));
	//}
	{
		const glm::mat4x4 matProj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
		const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		progSimple.SetViewProjectionMatrix(matProj * matView);
	}

	player.FontRender();
	Font& font = Font::Instance();

	if (state == State::hitPanel) {
		font.AddString("HitPanelNum", glm::vec3(-300,-200,0), glm::vec3(0), glm::vec3(3));
		font.AddString(pointList[hitPanelNum], glm::vec3(100,-200,0), glm::vec3(0), glm::vec3(3));

		
	}

	////�V�����`�揈��2d.
	SpriteRenderer& renderer = SpriteRenderer::Instance();
	renderer.AddSprite(&sprTest);
	renderer.Draw();
}

/**
* �I��.
*/
void MainGameScene::Finalize()
{
	ClearActorList(playerBulletList);
	ClearActorList(enemyList);
	ClearActorList(objectList);
	ClearActorList(frontPanelList);
	ClearActorList(footPanelList);

	//�����~�߂�
	backBGM->Stop();
}


/*
* �p�l���Ƃ̓����蔻������m����
*
*/
void MainGameScene::HitPanel()
{
	if (state == State::play) {
		//���p�l���Ƃ̓����蔻��
		if (player.position.y <= 0) {
			//x���͈͓�
			if (player.position.x >= 0 && player.position.x <= footPanel.x) {
				//����z���͈͓� �����if�ŏ����Ă��悩�������ǌ�����������̂Ńl�X�g
				if (player.position.z >= 0 && player.position.z <= footPanel.y) {
					//�����Ȃ�q�b�g�p�l��������
					state = State::hitPanel;
					//�߂荞�ݖh�~�̈ʒu����
					player.position.y = 0;
					player.stop = true;
					SEpanelHit->Play();
					stayPanelTimer = stayPanelTime;

					const int panelNum= PanelNumSpecific();
					hitPanelNum = panelNum;
					TotalPoint += pointList[panelNum];
				}
			}
		}
		//���ʃp�l���Ƃ̓����蔻��.
		if (player.position.z <= 0) {
			//x���͈͓�
			if (player.position.x > 0 && player.position.x <= frontPanel.x) {
				//����y���͈͓�
				if (player.position.y >= 0 && player.position.y <= frontPanel.y) {
					//�����Ȃ�p�l���q�b�g������
					state = State::hitPanel;
					//�߂荞�ݖh�~�̈ʒu����.
					player.position.z = 0;
					player.stop = true;
					SEpanelHit->Play();
					stayPanelTimer = stayPanelTime;

					const int panelNum= PanelNumSpecific();
					hitPanelNum = panelNum;
					TotalPoint += pointList[panelNum];

				}
			}
		}


	}
}

/*
* �v���C���[�̈ʒu�𐧌䂷��
* ����͂����܂ŗ����̂���͂ݏo�����Ȃ�߂��悤�ȏ��������Ă���     
*
*/
void MainGameScene::ControlPos()
{
	//�����H�𑖂��Ă��鎞�̏���
	if (playerArea == Area::RanWay)
	{
		//���ɉ����Ĉړ�����悤�ɒ���.
		player.position.y = ranwayOrigin.y;

		//��O�ɖ߂�Ȃ��悤�ɒ���.
		if (player.position.z >= footPanel.y+ranwaySize.z) {
			player.position.z = footPanel.y + ranwaySize.z;
		}
		//���E�ɂ͂ݏo�Ȃ��悤�ɒ���.
		if (player.position.x<=ranwayOrigin.x-ranwaySize.x/2) {
			player.position.x = ranwayOrigin.x - ranwaySize.x / 2;
		}
		else if (player.position.x >= ranwayOrigin.x + ranwaySize.x / 2) {
			player.position.x = ranwayOrigin.x + ranwaySize.x / 2;
		}

		//�v���C���[�������H�͈̔͊O�ɏo���Ƃ��ɃG���A��ύX����.
		if (player.position.z <= footPanel.y) {
			player.isGround = false;
			playerArea = Area::Air;
		}
	}
	//���󂵂Ă��鎞�̏���.
	else if (playerArea==Area::Air)
	{
		//�V�����ɍs���Ȃ��悤�ɐ���.
		if (player.position.y > frontPanel.y) {
			player.position.y = frontPanel.y;
		}
		//���E�ɂ͂ݏo�Ȃ��悤�ɐ���.
		if (player.position.x < 0) {
			player.position.x = 0;
		}
		else if (player.position.x > footPanel.x)
		{
			player.position.x = footPanel.x;
		}
		//��O�ɖ߂�Ȃ��悤�ɐ���.
		if (player.position.z >= footPanel.y)
		{
			player.position.z = footPanel.y;
		}
	}
}

/*
* �v���C���[�̈ʒu���W����Ԃ������p�l���̔ԍ�����肷��
* �]�k.���� specific
*
* retval : �Ԃ������p�l���ԍ�.
*/
int MainGameScene::PanelNumSpecific() {
	int num=0;

	//���ʃp�l���ɂԂ������ꍇ.
	if (player.position.z <= 0) {
		for (int i = 0; i < frontPanelAll;++i) {
			int w = i% frontWidthCount;//��
			int h = i/frontHeightCount;//�c
			//xy���ʂŃv���C���[���p�l���̂ǂ̈ʒu�ɂ��邩����������
			if (player.position.x >= frontOnePanel.x * w && player.position.x <= frontOnePanel.x * w + frontOnePanel.x
				&& player.position.y >= frontOnePanel.y * h && player.position.y <= frontOnePanel.y * h + frontOnePanel.y
				)
			{
				break;
				
			}
			//1���[�v����1�J�E���g����
			++num;
		}
	}



	//���p�l���ɂԂ������ꍇ.
	else if (player.position.y<=0) {
		//���ʂłȂ��Ȃ��.���ʕ������𑫂�
		num += frontPanelAll;
		for (int i = 0; i < footPanelAll; ++i) {
			int w = i % footWidthCount;//��
			int h = i / footHeightCount;//�c
			//xz���ʂŃv���C���[���p�l���̂ǂ̈ʒu�ɂ��邩����������
			if (player.position.x >= frontOnePanel.x * w && player.position.x <= frontOnePanel.x * w + frontOnePanel.x
				&& player.position.z >= frontOnePanel.y * h && player.position.z <= frontOnePanel.y * h + frontOnePanel.y
				)
			{
				break;
			}
			//1����
			++num;
		}
	}
	

	return num;
}


/*
* �d�؂蒼��.����������l�����˂�����ŏ��������銴��
*
*
*
*
*/
void MainGameScene::Restart() {


	player.position = playerStartPos;
	playerArea = Area::RanWay;
	++tryCount;
	player.stop = true;
	stanbyTimer = stanbyTime;
	state = State::StandBy;
	whiteOut.a = 1;
	player.resetParam();


	//���łȂ̂�bgm���d�؂蒼��
	backBGM->Stop();
	backBGM->Play(Audio::Flag_Loop);
	SEradyGo->Play();

}

/*
* �X�^�[�g����O�̑ҋ@����
*
* deltatime�擾�Ɉ����ݒ��window�擾���Ăǂ����������񂩂�?2/13
*
*/
void MainGameScene::StandBy() {
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime = window.DeltaTime();

	if (stanbyTimer>=0) {
		stanbyTimer -= deltaTime;

	}
	else {
		state = State::play;
		whiteOut.a = 0;
		player.stop = false;
	}
	if (whiteOut.a > 0) {
		whiteOut.a -= deltaTime;
		if (whiteOut.a <= 0) {
			whiteOut.a = 0;
		}
	}


}

/*
* �p�l���ɗ��܂鏈��
*
*
*
*/
void MainGameScene::StayPanel() {
	if (state == State::hitPanel) {
		//�^�C�}�[��0�łȂ���΍X�V
		GLFWEW::Window& window = GLFWEW::Window::Instance();
		float deltaTime = window.DeltaTime();
		if (stayPanelTimer > 0) {
			stayPanelTimer -= deltaTime;
			if (stayPanelTimer <= stayPanelTime - 1) {
				whiteOut.a += deltaTime / 2.0f;
			}
		}
		else {

			if (tryCount < tryMax) {
				Restart();
			}
			else {
				GoResult();
			}
		}

	}

}


//���U���g�V�[���Ɉڍs���鏈��
void MainGameScene::GoResult() {
	
	
	NextScene("Result");
	ResultScene::setResultPoint(TotalPoint);
}

