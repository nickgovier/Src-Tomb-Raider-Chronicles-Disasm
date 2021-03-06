#include "CALCLARA.H"

#include "SPECIFIC.H"
#include "DRAW.H"
#include "LARA.H"
#include "GTEREG.H"
#include "DELSTUFF.H"
#include "LOAD_LEV.H"
#include "CAMERA.H"
#include "CONTROL.H"

void S_SetupClutAdder(long underwater)
{
	DQB = underwater;
}

void SetRotation_CL(int t0, int t1, int t2, int t3, int t4)
{
	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4 & 0xFFFF;
}

void setup_rotation_matrix(int* mat)
{
	SetRotation_CL(mat[0], mat[1], mat[2], mat[3], mat[4]);
}

void copy_matrix_from_scratch(int* a0, int* a1)
{
	int t0 = a0[0];
	int t1 = a0[1];
	int t2 = a0[2];
	int t3 = a0[3];
	a1[0] = t0;
	a1[1] = t1;
	a1[2] = t2;
	a1[3] = t3;
	int t4 = a0[4];
	int t5 = a0[5];
	int t6 = a0[6];
	int t7 = a0[7];
	a1[4] = t4;
	a1[5] = t5;
	a1[6] = t6;
	a1[7] = t7;
}

void mLoadMatrix(int* mat)
{
	TRX = mat[5];
	TRY = mat[6];
	TRZ = mat[7];

	SetRotation_CL(mat[0], mat[1], mat[2], mat[3], mat[4]);
}

void mRotY_CL(long y)
{
	y >>= 2;
	y &= 0x3FFC;
	
	if (y != 0)
	{

		//loc_84DA4
		int t5 = ((int*)&rcossin_tbl[y >> 2])[0];
		int t7 = 0xFFFF0000;
		int t6 = t5 >> 16;
		t5 &= 0xFFFF;
		int t2 = -t5;

		VX0 = t6 & 0xFFFF;
		VX1 = (t6 >> 16) & 0xFFFF;
		VZ0 = t2;

		int t0 = R11 | (R12 << 16);
		t2 = R22 | (R23 << 16);
		int t3 = R31 | (R32 << 16);

		docop2(0x486012);

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6 & 0xFFFF;

		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;

		int t4 = MAC1;
		int t1 = MAC2;
		t5 = MAC3;

		docop2(0x48E012);

		t4 &= 0xFFFF;
		t0 |= t4;
		t1 <= 16;
		t5 &= 0xFFFF;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_CL(t0, t1, t2, t3, t4);
	}
}

void SetRotation_CL_I(int t0, int t1, int t2, int t3, int t4)
{
	L11 = (t0 & 0xFFFF);
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = (t1 & 0xFFFF);
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = (t2 & 0xFFFF);
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = (t3 & 0xFFFF);
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = (t4 & 0xFFFF);
}

void iRotY_CL(long y)
{
	y >>= 2;
	y &= 0x3FFC;

	if (y != 0)
	{
		int t5 = ((int*)&rcossin_tbl[y >> 2])[0];
		int t7 = 0xFFFF0000;
		int t6 = t5 >> 16;
		t5 &= 0xFFFF;
		int t2 = -t5;

		VX0 = (t6 & 0xFFFF);
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = (t2 & 0xFFFF);

		int t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
		t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
		int t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

		docop2(0x4A6012);

		VX1 = (t5 & 0xFFFF);
		VY1 = ((t5 >> 16) & 0xFFFF);
		VZ1 = (t6 & 0xFFFF);

		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;

		int t4 = MAC1;
		int t1 = MAC2;
		t5 = MAC3;

		docop2(0x4AE012);

		t4 &= 0xFFFF;
		t0 |= t4;
		t1 <<= 16;
		t5 &= 0xFFFF;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;
		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;
		
		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void iRotX_CL(long x)
{
	x >>= 2;
	x &= 0x3FFC;

	if (x != 0)
	{
		int t5 = ((int*)&rcossin_tbl[x >> 2])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = (t6 & 0xFFFF);
		VY0 = ((t6 >> 16) & 0xFFFF);
		VZ0 = (t5 & 0xFFFF);

		int t0 = L11 | (L12 << 16);
		int t1 = L13 | (L21 << 16);
		int t3 = L31 | (L32 << 16);

		docop2(0x4A6012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = (t5 & 0xFFFF);
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6 & 0xFFFF;

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		int t4 = MAC1;
		int t2 = MAC2;
		t5 = MAC3;

		docop2(0x4AE012);

		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <= 16;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void iRotZ_CL(long z)
{
	z >>= 2;
	z &= 0x3FFC;

	if (z != 0)
	{
		int t0 = ((int*)&rcossin_tbl[z >> 2])[0];
		int t7 = 0xFFFF0000;
		int t1 = t0 >> 16;
		int t2 = t0 << 16;
		t1 |= t2;

		R11 = (t1 & 0xFFFF);
		R12 = (t1 >> 16) & 0xFFFF;
		R13 = 0;
		R21 = 0;

		t1 = (L13 & 0xFFFF) || (L21 << 16);
		t2 = (L22 & 0xFFFF) || (L23 << 16);
		int t4 = (L33 & 0xFFFF);
		docop2(0x4A6012);
		int t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;
		VX1 = (t0 & 0xFFFF);
		VY1 = ((t0 >> 16) & 0xFFFF);
		VZ1 = 0;
		t1 &= 0xFFFF;
		t0 = MAC1;
		int t5 = MAC2;
		t3 = MAC3;

		docop2(0x4AE012);
		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;
		t5 = MAC1;
		int t6 = MAC2;
		t7 = MAC3;
		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		t7 <<= 16;
		t3 |= t7;

		//loc_85204
		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void mRotX_CL(long x)
{
	x >>= 2;
	x &= 0x3FFC;

	if (x != 0)
	{
		//loc_84D04
		int t5 = ((int*)&rcossin_tbl[x >> 2])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = (t5 & 0xFFFF);

		int t0 = R11 | (R12 << 16);
		int t1 = R13 | (R21 << 16);
		int t3 = R31 | (R32 << 16);

		docop2(0x486012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = (t5 & 0xFFFF);
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = (t6 & 0xFFFF);

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		int t4 = MAC1;
		int t2 = MAC2;
		t5 = MAC3;

		docop2(0x48E012);

		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <<= 16;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_CL(t0, t1, t2, t3, t4);
	}
}

void mRotZ_CL(long z)
{
	z >>= 2;
	z &= 0x3FFC;

	if (z != 0)
	{
		int t0 = ((int*)&rcossin_tbl[z >> 2])[0];
		int t7 = 0xFFFF0000;
		int t1 = t0 >> 16;
		int t2 = t0 << 16;
		t1 |= t2;
		VX0 = t1 & 0xFFFF;
		VY0 = (t1 >> 16) & 0xFFFF;
		VZ0 = 0;

		t1 = R13 | (R21 << 16);
		t2 = R22 | (R23 << 16);
		int t4 = R33;

		docop2(0x486012);
		int t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;

		VX1 = t0 & 0xFFFF;
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;

		t1 &= 0xFFFF;

		t0 = MAC1;
		int t5 = MAC2;
		t3 = MAC3;

		docop2(0x48E012);

		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;

		t5 = MAC1;
		int t6 = MAC2;
		int a0 = MAC3;

		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		a0 <<= 16;
		t3 |= a0;

		SetRotation_CL(t0, t1, t2, t3, t4);
	}//loc_84E5C
}

void mRotYXZ_CL(long y, long x, long z)
{
	mRotY_CL(y);
	mRotX_CL(x);
	mRotZ_CL(z);
}

void iRotSuperPackedYXZ_CL(int* t8, int a1)
{
	unsigned short* a2 = (unsigned short*)t8[10];
	unsigned short v0;

	if (a1 != 0)
	{
		do
		{
			//loc_85228
			v0 = a2[0];
			a1--;
			if (!(v0 & 0xC000))
			{
				a2++;
			}

			a2++;
			//loc_85240
		} while (a1 != 0);

		v0 = a2[0];
	}
	//loc_8524C
	a2++;
	
	int at = v0 >> 14;
	if (at-- != 0)
	{
		t8[10] = (int)a2;

		if (at-- != 0)
		{
			int a0 = v0 & 0xFFF;
			if (at != 0)
			{
				iRotZ_CL(a0 << 4);
			}
			//loc_85278
			iRotY_CL(a0 << 4);
		}//loc_85280
		int a0 = v0 & 0xFFF;
		iRotX_CL(a0 << 4);
	}//loc_8528C

	at = *a2++;
	t8[10] = (int)a2;
	int a22 = v0 << 16;
	a22 |= at;

	iRotY_CL((a22 >> 4) & 0xFFC0);
	iRotX_CL((a22 >> 14) & 0xFFC0);
	iRotZ_CL((a22 << 6) & 0xFFC0);
}

void mRotSuperPackedYXZ_CL(int* t8, int a1)
{
	return;///crashing
	unsigned short* a2 = (unsigned short*)t8[6];
	unsigned short v0;

	if (a1 != 0)
	{
		//loc_84C48
		do
		{
			v0 = a2[0];
			a1--;
			a2++;
			if (!(v0 & 0xC000))
			{
				a2++;
			}
			//loc_84C60
		} while (a1 != 0);
	}
	//loc_84C6C
	a2++;
	int at = v0 >> 14;

	if (at-- != 0)
	{
		t8[9] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				mRotZ_CL((v0 & 0xFFF) << 4);
			}
			//loc_84C98
			mRotY_CL((v0 & 0xFFF) << 4);
		}
		//loc_84CA0
		mRotX_CL((v0 & 0xFFF) << 4);

	}//loc_84CAC

	at = a2[0];
	a2++;
	t8[9] = (int)a2;
	v0 <<= 16;
	v0 |= at;

	mRotY_CL((v0 >> 4) & 0xFFC0);
	mRotX_CL((v0 >> 14) & 0xFFC0);
	mRotZ_CL((v0 & 0x3FF) << 6);
}

void iTranslateXYZ2_CL(long x /*a3*/, long y /*a1*/, long z /*a2*/)
{
	int t0 = x >> 15;
	if (x < 0)
	{
		x = -x;
		t0 = x >> 15;
		x &= 0x7FFF;
		t0 = -t0;
		x = -x;
	}
	else
	{
		//loc_85318
		x &= 0x7FFF;
	}

	int t1 = y >> 15;
	if (y < 0)
	{
		y = -y;
		t1 = y >> 15;
		y & -0x7FFF;
		t1 = -t1;
		y = -y;
	}
	else
	{
		//loc_8533C
		y &= 0x7FFF;
	}

	//loc_85340
	int t2 = z >> 15;
	if (t2 < 0)
	{
		z = -z;
		t2 = z >> 15;
		z &= 0x7FFF;
		t2 = -t2;
		z = -z;
	}
	else
	{
		//loc_85360
		z &= 0x7FFF;
	}

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x43E012);

	int t6 = MAC1;

	IR1 = x;
	IR2 = y;
	IR3 = z;

	int t7 = MAC2;
	int v0 = MAC3;

	docop2(0x4BE012);

	int t3 = t6 << 3;
	if (t3 < 0)
	{
		t6 = -t6;
		t6 <<= 3;
		t3 = -t6;
	}

	//loc_853A8
	int t4 = t7 << 3;
	if (t7 < 0)
	{
		t7 = -t7;
		t7 <<= 3;
		t4 = -t7;
	}

	//loc_853BC
	int t5 = v0 << 3;
	if (v0 < 0)
	{
		v0 = -v0;
		v0 <<= 3;
		t5 = -v0;
	}

	//loc_853D0
	t6 = MAC1;
	t7 = MAC2;
	v0 = MAC3;

	t3 += t6;
	t4 += t7;
	t5 += v0;

	t0 = RBK;
	t1 = GBK;
	t2 = BBK;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	RBK = t0;
	GBK = t1;
	BBK = t2;
}

void mTranslateXYZ_CL(long x, long y, long z)
{
	int t4 = y >> 15;
	if (y < 0)
	{
		y = -y;
		t4 = y >> 15;
		y &= 0x7FFF;
		t4 = -t4;
		y = -y;
	}
	else
	{
		y &= 0x7FFF;
	}

	//loc_84B5C
	int t5 = z >> 15;
	if (z < 0)
	{
		z = -z;
		t5 = z >> 15;
		z &= 0x7FFF;
		t5 = -t5;
		z = -z;
	}
	else
	{
		//loc_84B80
		z &= 0x7FFF;
	}

	int t3 = x >> 15;
	if (x < 0)
	{
		x = -x;
		t3 = x >> 15;
		x &= 0x7FFF;
		t3 = -t3;
		x = -x;
	}
	else
	{
		//loc_84BA4
		x &= 0x7FFF;
	}

	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = x;
	IR2 = y;
	IR3 = z;

	docop2(0x498012);

	int t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}

	//loc_84BEC
	int t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_84C00
	int t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}

	//loc_84C14
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;
}

void mTranslateAbsXYZ_CL(long x, long y, long z)
{
	TRX = 0;
	TRY = 0;
	TRZ = 0;

	mTranslateXYZ_CL(x - ((int*)& MatrixStack[0])[5], y - ((int*)& MatrixStack[0])[6], z - ((int*)& MatrixStack[0])[7]);
}

void Hardcore_mTranslateXYZ_CL(long* a2)
{
	mTranslateXYZ_CL(a2[0], a2[1], a2[2]);
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
	int sp[256];
	int* t8 = &sp[0];
	struct ITEM_INFO* item = lara_item;
	short* t9 = frame;
	long* s1 = bone;
	frame += 4;
	GLaraShadowframe = t9;
	t8[9] = (int)frame;
	snaff_current_gte_matrix_V1(&t8[38]);
	struct MATRIX3D* a0 = NULL;

	if ((flag & 0x1))
	{
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		t8[13] = (int)lara_joint_matrices;
	}
	else
	{
		//loc_83C40
		t8[13] = (int)lara_matrices;
		mTranslateAbsXYZ_CL(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		if ((flag & 0x2))
		{
			ScaleCurrentMatrix(0, -4096, -4096, -4096);
		}
	}
	//loc_83C74
	mRotYXZ_CL(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
	snaff_current_gte_matrix_V1(&t8[14]);
	mTranslateXYZ_CL(t9[6], t9[7], t9[8]);
	mRotSuperPackedYXZ_CL(t8, 0);

	int* s0 = &t8[13];
	snaff_current_gte_matrix_V1(&t8[22]);
	int a3 = 6;

	//loc_83CB4
	do
	{
		Hardcore_mTranslateXYZ_CL(&s1[1]);
		mRotSuperPackedYXZ_CL(&t8[22], 0);
		snaff_current_gte_matrix_V1(&s0[8]);
		a3--;

		s1 += 4;
		if (a3 == 3)
		{
			mLoadMatrix(&t8[22]);
		}//loc_83CE4

		s0 += 8;

	} while (a3 != 0);

	mLoadMatrix(&t8[22]);
	bone -= 24;
	s0 -= 48;

	Hardcore_mTranslateXYZ_CL(&s1[25]);

	if (lara.weapon_item != -1 && lara.gun_type == 5 &&
		(items[lara.weapon_item + 1].frame_number == 0 ||
			items[lara.weapon_item + 1].frame_number == 2 ||
			items[lara.weapon_item + 1].frame_number == 4))
	{
		t8[9] = (int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
		mRotSuperPackedYXZ_CL(t8, 7);
	}
	else
	{
		//loc_83DA8
		mRotSuperPackedYXZ_CL(t8, 0);
	}

	mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	snaff_current_gte_matrix_V1(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[53]);
	mRotSuperPackedYXZ_CL(t8, 6);
	///@TODO debug this on PSX, mRotSuperPackedYXZ must implicitly change t8[9] and the value is popped back
	//a3 = t8[9];
	//?????? sw      a3, 0x24(t8)
	mRotYXZ_CL(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	snaff_current_gte_matrix_V1(&s0[64]);
	mLoadMatrix(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[29]);

	if (lara.gun_status == 2 || lara.gun_status == 3 ||
		lara.gun_status == 4 || lara.gun_status == 5)
	{
		switch (lara.gun_type)
		{
		case 0:
		case 7:
		case 8:
		{
		loc_83E60:
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);

			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			if (lara.flare_control_left)
			{
				((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
				mRotSuperPackedYXZ_CL(&t8[0], 11);
			}
			else
			{
				//loc_83F14
				mRotSuperPackedYXZ_CL(&t8[0], 0);
			}

			//loc_83F18
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 1:
		case 3:
		{
			//loc_83F5C
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.right_arm.y_rot, lara.right_arm.x_rot, lara.right_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.left_arm.y_rot, lara.left_arm.x_rot, lara.left_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 2:
		{
			//loc_840B0
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 4:
		case 5:
		case 6:
		{
			//loc_84204
			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 9:///@FIXME Says < 0xA investigate me!
		{
			break;
		}
		}
	}
	else
	{
		goto loc_83E60;
	}

	copy_matrix_from_scratch(&t8[22], s0);
	copy_matrix_from_scratch(&t8[30], &s0[56]);
	mLoadMatrix(&t8[38]);
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate, long* bone, int flag)
{
	int sp[256];
	int* t8 = &sp[0];
	struct ITEM_INFO* item = lara_item;//$t9
	short* s0 = frame1;
	short* s1 = frame2;
	//long* s1 = bone;
	frame1 += 4;
	frame2 += 4;
	t8[9] = (int)frame1;
	t8[10] = (int)frame2;
	snaff_current_gte_matrix_V1(&t8[72]);
	struct MATRIX3D* a0 = NULL;

	if ((flag & 0x1))
	{
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		t8[13] = (int)lara_joint_matrices;
	}
	else
	{
		//loc_83C40
		t8[13] = (int)lara_matrices;
		mTranslateAbsXYZ_CL(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		if ((flag & 0x2))
		{
			ScaleCurrentMatrix(0, -4096, -4096, -4096);
		}
	}

	//loc_83C74
	mRotYXZ_CL(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
	snaff_current_gte_matrix_V1(&t8[64]);
	L11 = R11;
	L12 = R12;
	L13 = R13;
	L21 = R21;
	L22 = R22;
	L23 = R23;
	L31 = R31;
	L32 = R32;
	L33 = R33;
	RBK = TRX;
	GBK = TRY;
	BBK = TRZ;

	mTranslateXYZ_CL(s0[6], s0[7], s0[8]);
	iTranslateXYZ2_CL(s1[6], s1[7], s1[8]);
	mRotSuperPackedYXZ_CL(t8, 0);
	iRotSuperPackedYXZ_CL(t8, 0);

#if 0
	

	int* s0 = &t8[13];
	snaff_current_gte_matrix_V1(&t8[22]);
	int a3 = 6;

	//loc_83CB4
	do
	{
		Hardcore_mTranslateXYZ_CL(&s1[1]);
		mRotSuperPackedYXZ(&t8[22], 0);
		snaff_current_gte_matrix_V1(&s0[8]);
		a3--;

		s1 += 4;
		if (a3 == 3)
		{
			mLoadMatrix(&t8[22]);
		}//loc_83CE4

		s0 += 8;

	} while (a3 != 0);

	mLoadMatrix(&t8[22]);
	bone -= 24;
	s0 -= 48;

	Hardcore_mTranslateXYZ_CL(&s1[25]);

	if (lara.weapon_item != -1 && lara.gun_type == 5 &&
		(items[lara.weapon_item + 1].frame_number == 0 ||
			items[lara.weapon_item + 1].frame_number == 2 ||
			items[lara.weapon_item + 1].frame_number == 4))
	{
		t8[9] = (int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
		mRotSuperPackedYXZ(t8, 7);
	}
	else
	{
		//loc_83DA8
		mRotSuperPackedYXZ(t8, 0);
	}

	mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	snaff_current_gte_matrix_V1(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[53]);
	mRotSuperPackedYXZ(t8, 6);
	///@TODO debug this on PSX, mRotSuperPackedYXZ must implicitly change t8[9] and the value is popped back
	//a3 = t8[9];
	//?????? sw      a3, 0x24(t8)
	mRotYXZ_CL(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	snaff_current_gte_matrix_V1(&s0[64]);
	mLoadMatrix(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[29]);

	if (lara.gun_status == 2 || lara.gun_status == 3 ||
		lara.gun_status == 4 || lara.gun_status == 5)
	{
		switch (lara.gun_type)
		{
		case 0:
		case 7:
		case 8:
		{
		loc_83E60:
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);

			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			if (lara.flare_control_left)
			{
				((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
				mRotSuperPackedYXZ(&t8[0], 11);
			}
			else
			{
				//loc_83F14
				mRotSuperPackedYXZ(&t8[0], 0);
			}

			//loc_83F18
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 1:
		case 3:
		{
			//loc_83F5C
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.right_arm.y_rot, lara.right_arm.x_rot, lara.right_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.left_arm.y_rot, lara.left_arm.x_rot, lara.left_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 2:
		{
			//loc_840B0
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 4:
		case 5:
		case 6:
		{
			//loc_84204
			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 9:///@FIXME Says < 0xA investigate me!
		{
			break;
		}
		}
	}
	else
	{
		goto loc_83E60;
	}

	copy_matrix_from_scratch(&t8[22], s0);
	copy_matrix_from_scratch(&t8[30], &s0[56]);
	mLoadMatrix(&t8[38]);
#endif
}

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C
{
#if 0///@FIXME see getframes comment
	int rate;
	short* frmptr[2];
	int frac = GetFrames(item, frmptr, &rate);//TODO local GETFRAMES!

	if (frac == 0)
		return frmptr[0];

	short* bptr = interpolated_bounds;

	for (int i = 0; i < 6; i++, bptr++, frmptr[0]++, frmptr[1]++)
	{
		*bptr = *frmptr[0] + (*frmptr[1] - *frmptr[0]) * frac / rate;
	}
#endif
	return interpolated_bounds;
}

void snaff_current_gte_matrix_V1(int* mat)
{
	mat[0] = R11 | (R12 << 16);
	mat[1] = R13 | (R21 << 16);
	mat[2] = R22 | (R23 << 16);
	mat[3] = R31 | (R32 << 16);
	mat[4] = R33;
	mat[5] = TRX;
	mat[6] = TRY;
	mat[7] = TRZ;
}

void GetLaraJointPos(struct PHD_VECTOR* pos, long joint)
{
	UNIMPLEMENTED();
}

short* GetBestFrame(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
	return NULL;
}