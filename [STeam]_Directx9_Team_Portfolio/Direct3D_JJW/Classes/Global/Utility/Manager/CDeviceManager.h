#pragma once

#include "../../Define/KGlobalDefine.h"

/*
���̷�Ʈ 3D�� �޸� ���� ������� ���� ī���� ����� ä���ϰ� �ִ�
���� ī��Ʈ�� ������ų���� AddRef �Լ�,
���� ī��Ʈ�� ���ҽ�ų���� Release �Լ��� �̿��ϸ� �ȴ�
(�P, ���������� delete�� ȣ���Ű�� ���� �����Ǿ��ִ�)

IUnknown �������̽��� ����ϴ� ��� Ŭ������ �ش� ����� �޸� ���� ��Ģ��
������Ѵ� (iUnknown �������̽��� ����ϴ� Ŭ������ ���ξ I�� �����Ѵ�)

AddRef �Լ��� ȣ��Ǵ� ������ IUnknown �������̽��� ����� Ŭ������ Get�Լ��� �����ö��̴�
(��, Get �Լ��� ���� ��ü�� �����Ӵٸ� ���� Release �Լ��� ȣ���� �־���Ѵ�)
*/

//! ����̽� ������
class CDeviceManager
{
public:				// ����

	//! ���̷�Ʈ 3D�� ��ȯ�Ѵ�
	LPDIRECT3D9 getDirect3D(void);

	//! ����̽��� ��ȯ�Ѵ�
	LPDIRECT3DDEVICE9 getDevice(void);

public:				// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CDeviceManager);

	//! �ʱ�ȭ
	virtual void init(HWND a_hWindow,
		const SIZE a_stWindowSize);

private:			// private �Լ�

	/*
	Direct3D�� �׷��� ī���� �������� ������ ����ϴµ� ���ȴ�.
	(���� Device�� �����ϱ� �������� �̿��� �ǰ�, ���Ŀ��� �� ������ �ʴ´�)
	*/
	//! ���̷�Ʈ 3D�� �����Ѵ�
	LPDIRECT3D9 createDirect3D(void);


	/*
	Direct3D Device�� �������� �׷��� ī�带 �����ϴ� Ŭ�����̴�.
	(��, Device�� ���ؼ� 3���� ��ü ���� �������� ��Ÿ����)
	*/
	//! ����̽��� �����Ѵ�
	LPDIRECT3DDEVICE9 createDevice(HWND a_hWindow,
		const SIZE a_stWindowSize);

private:			// �Ҹ���

	//! �Ҹ���
	virtual ~CDeviceManager(void);

private:			// private ����

	LPDIRECT3D9 m_pDirect3D = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
};