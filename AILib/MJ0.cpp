/*
* MJ0.c
* �Ƃ������k����MJ-0 �A���S���Y�����������܂�(on �܂������IF)
* �A���S���Y���̒��쌠�͂Ƃ������k�������L���܂�
* �܂������̒��쌠�͐Δ������������L���܂�
* �v���O�����̒��쌠��kacky�����L���܂�
*/
/****************************************************************************************
* Copyright (c) 2016, Takaya Kakizaki(kacky)
* All rights reserved.

�\�[�X�R�[�h�`�����o�C�i���`�����A�ύX���邩���Ȃ������킸�A�ȉ��̏����𖞂����ꍇ�Ɍ���A�ĔЕz����юg�p��������܂��B

�E�\�[�X�R�[�h���ĔЕz����ꍇ�A��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ������܂߂邱�ƁB

�E�o�C�i���`���ōĔЕz����ꍇ�A�Еz���ɕt���̃h�L�������g���̎����ɁA��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ������܂߂邱�ƁB

�E���ʂɂ����ʂ̋��Ȃ��ɁA�{�\�t�g�E�F�A����h���������i�̐�`�܂��͔̔����i�ɁA�I�[�v�������̖��O�܂��̓R���g���r���[�^�[�̖��O���g�p���Ă͂Ȃ�Ȃ��B


�{�\�t�g�E�F�A�́A���쌠�҂���уR���g���r���[�^�[�ɂ���āu����̂܂܁v�񋟂���Ă���A�����َ����킸�A
���ƓI�Ȏg�p�\���A����ѓ���̖ړI�ɑ΂���K�����Ɋւ���Öق̕ۏ؂��܂߁A�܂�����Ɍ��肳��Ȃ��A�����Ȃ�ۏ؂�����܂���B
���쌠�҂��R���g���r���[�^�[���A���R�̂�������킸�A ���Q�����̌�����������킸�A���ӔC�̍������_��ł��邩���i�ӔC�ł��邩
�i�ߎ����̑��́j�s�@�s�ׂł��邩���킸�A���ɂ��̂悤�ȑ��Q����������\����m�炳��Ă����Ƃ��Ă��A�{�\�t�g�E�F�A�̎g�p�ɂ���Ĕ�������
�i��֕i�܂��͑�p�T�[�r�X�̒��B�A�g�p�̑r���A�f�[�^�̑r���A���v�̑r���A�Ɩ��̒��f���܂߁A�܂�����Ɍ��肳��Ȃ��j
���ڑ��Q�A�Ԑڑ��Q�A�����I�ȑ��Q�A���ʑ��Q�A�����I���Q�A�܂��͌��ʑ��Q�ɂ��āA��ؐӔC�𕉂�Ȃ����̂Ƃ��܂��B

****************************************************************************************/


#include "MJ0.h"
#include <array>
#include <numeric>
#include <vector>

#define SIMU_SIZE (5000)

using namespace std;

namespace MJAI {
	vector<Mentsu> Mentsu::_all;
	vector<Mentsu> Mentsu::_all_atama;

	int paidistance(const std::vector<Pai>&tehai, int pai) {
		int i;
		unsigned prev = 0, n = 0;
		unsigned distp, distn;
		pai &= 0x3F;

		for (i = 0; i < tehai.size(); i++) {
			n = tehai[i].getNum() & 0x3F;
			/* ���݂��Ȃ��v�͔�΂�(��v�𔲂��o���ꍇ�ɕ֗�) */
			if (n>33) continue;

			if (n >= pai) {
				if (pai >= 27) {
					/* ���v */
					return (n == pai) ? 0 : -1;
				}
				else if ((pai % 9) == 0) {
					/* ���݁A����A�ꓛ */
					return (n - pai < 9) ? (n - pai) : -1;
				}
				else if ((pai % 9) == 8) {
					/* ���݁A����A�㓛 */
					return (pai - prev < 9) ? (pai - prev) : -1;
				}
				else {
					/* ���̑��̔v */

					/* ���̔v�Ƃ̋���(��ނ��Ⴄ�ꍇ��99) */
					if (n / 9 == pai / 9) {
						distn = n - pai;
					}
					else {
						distn = 99;
					}

					/* �O�̔v�Ƃ̋���(��ނ��Ⴄ�ꍇ��99) */
					if (prev / 9 == pai / 9) {
						distp = pai - prev;
					}
					else {
						distp = 99;
					}

					/* ����������Ԃ� */
					if (distn > distp) {
						return (distp < 9) ? distp : -1;
					}
					else {
						return (distn < 9) ? distn : -1;
					}
				}

			}
			prev = n;

		}

		/* ������Ȃ�(�܂莩������Ԍ��) */
		if (pai >= 27) {
			/* ���v */
			return -1;
		}
		else if ((pai % 9) == 0) {
			/* ���݁A����A�ꓛ */
			return -1;
		}
		else if ((pai % 9) == 8) {
			/* ���݁A����A�㓛 */
			return (pai - prev < 9) ? (pai - prev) : -1;
		}
		else {
			/* ���̑��̔v */

			/* �O�̔v�Ƃ̋���(��ނ��Ⴄ�ꍇ��99) */
			if (prev / 9 == pai / 9) {
				distp = pai - prev;
			}
			else {
				distp = 99;
			}

			return (distp < 9) ? distp : -1;
		}

	}
	void MJ0::simulate(Players *players, Player *myself, vector<Pai> *doras)
	{
		PaiArray nokorihai(4.0f), pai_kukan;
		auto mentsu_full = [](Player &p) {return p._mentsu.size() + p._naki_mentsu.size() < 4; };

		for (auto &player : *players) {
			player._anpai = PaiArray();
			player._kikenhai = PaiArray();
			for (auto pai : player._tehai) {
				nokorihai[pai.getNum()] -= 1.0f;
			}

			for (auto pai : player._kawahai) {
				if (!pai.isNaki()) nokorihai[pai.getNum()] -= 1.0f;
				player._anpai[pai.getNum()] = 1.0f;
			}

			for (auto m : player._naki_mentsu) {
				m.sub(&nokorihai);
			}

			player._mentsu.clear();
		}

		myself->_kikenhai = PaiArray();

		for (auto dora : *doras) {
			nokorihai[dora.getDorahyouji()] -= 1.0f;
		}

		for (size_t i = 0; i < SIMU_SIZE; i++) {
			for (auto &player : *players) {
				player._pai_kukan = nokorihai;
			}

			myself->_pai_kukan = nokorihai;

			Players::iterator it;
			while ((it = find_if(players->begin(), players->end(), mentsu_full))
				   != players->end()) {
				while ((it = find_if(it, players->end(), mentsu_full))
					   != players->end()) {
					auto all = Mentsu::all();
					const auto &pai_kukan = it->_pai_kukan;
					// �����c�������_���Œ��o����
					float sum = accumulate(all.cbegin(), all.cend(), 0.0f, [pai_kukan](float a,const Mentsu &m) { return a + m.weight(pai_kukan); });
					float val = rand() * sum / RAND_MAX;
					float tmp = 0.0f;
					auto mentsu = find_if(all.cbegin(), all.cend(), [val, tmp, pai_kukan](const Mentsu &m) mutable { tmp += m.weight(pai_kukan); return val < tmp; });
					(it->_mentsu).push_back(*mentsu);

					// �����c���\������v��v��Ԃ��珜������
					for (auto &p2 : *players)
					{
						mentsu->sub(&p2._pai_kukan);
					}
					mentsu->sub(&myself->_pai_kukan);

					// �v�̊댯�x���X�V����
					mentsu->addKiken(&it->_kikenhai);
					mentsu->addKiken(&myself->_kikenhai);
					it++;
				}
			}

			for (auto &player : *players) {
				auto all = Mentsu::all_atama();
				const auto &pai_kukan = player._pai_kukan;
				// �A�^�}�������_���Œ��o����
				float sum = accumulate(all.cbegin(), all.cend(), 0.0f, [pai_kukan](float a, const Mentsu &m) { return a + m.weight(pai_kukan); });
				float val = rand() * sum / RAND_MAX;
				float tmp = 0.0f;
				auto mentsu = find_if(all.cbegin(), all.cend(), [val, tmp, pai_kukan](const Mentsu &m) mutable { tmp += m.weight(pai_kukan); return val <= tmp; });
				(player._mentsu).push_back(*mentsu);

				// �A�^�}���\������v��v��Ԃ��珜������
				for (auto &p2 : *players)
				{
					mentsu->sub(&p2._pai_kukan);
				}
				mentsu->sub(&myself->_pai_kukan);

				// �v�̊댯�x���X�V����
				mentsu->addKiken(&player._kikenhai);
				mentsu->addKiken(&myself->_kikenhai);
			}

			pai_kukan += myself->_pai_kukan;
		}

		myself->_pai_kukan = pai_kukan / SIMU_SIZE;
		myself->_kikenhai = myself->_kikenhai / SIMU_SIZE;
	}
} // MJAI
