#pragma once

class SharedGameData {
public: //������
	void Init();
private:
	SharedGameData() = default;
	~SharedGameData() = default;
	// �R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜
	const SharedGameData& operator=(const SharedGameData&) = delete;
public:
	static SharedGameData* GetInstance();


public: //Getter
	//�@�I�΂�Ă�X�e�[�W�̔ԍ�
	int GetSelectedStageNo() const { return selectedStageNo_; } // 0:�X�e�[�W1, 1:�X�e�[�W2, 2:�X�e�[�W3, 3:�X�e�[�W4
public: //Setter
	//�@�I�΂�Ă�X�e�[�W�̔ԍ�
	void SetSelectedStageNo(int stageNo) { selectedStageNo_ = stageNo; } // 0:�X�e�[�W1, 1:�X�e�[�W2, 2:�X�e�[�W3, 3:�X�e�[�W4

public: // ���L����f�[�^
	//�@�I�΂�Ă�X�e�[�W�̔ԍ�
	int selectedStageNo_ = 0; // 0:�X�e�[�W1, 1:�X�e�[�W2, 2:�X�e�[�W3, 3:�X�e�[�W4
};