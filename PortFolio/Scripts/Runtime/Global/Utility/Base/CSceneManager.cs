using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 씬 관리자
public class CSceneManager : CComponent
{
	//! UI 카메라 프로퍼티
	public static Camera UICamera
	{
		get
		{
			return Function.FindComponent<Camera>(KDefine.NAME_UI_CAMERA);
		}
	}

	//! 메인 카메라 프로퍼티
	public static Camera MainCamera
	{
		get
		{
			return Function.FindComponent<Camera>(KDefine.NAME_MAIN_CAMERA);
		}
	}

	//! 씬 관리자 프로퍼티
	public static CSceneManager CurrentSceneManager
	{
		get
		{
			return Function.FindComponent<CSceneManager>(KDefine.NAME_SCENE_MANAGER);
		}
	}

	//! UI 루트 프로퍼티
	public static GameObject UIRoot
	{
		get
		{
			return GameObject.Find(KDefine.NAME_UI_ROOT);
		}
	}

	//! 객체 루트 프로퍼티
	public static GameObject ObjectRoot
	{
		get
		{
			return GameObject.Find(KDefine.NAME_OBJECT_ROOT);
		}
	}

	//! 초기화
	public override void Awake()
    {
        base.Awake();
        
		// 카메라를 설정한다
        this.SetupUICamera();
        this.SetupMainCamera();

		// 싱글턴 객체를 생성한다
		CSoundManager.Create();
		CResourceManager.Create();
		CUnityMessageSender.Create();
		CDeviceMessageReceiver.Create();
		CItemStorage.Create();
		CPlayerStorage.Create();
		CCardStorage.Create();
		CEnemyStorage.Create();
		// 문자열 리스트를 불러온다
		CLocalizeManager.Instance.ResetStringList();
		CLocalizeManager.Instance.LoadStringListFromFile("Datas/Localize/EN_LocalizeStrings");

        // 해상도를 변경한다
        Screen.SetResolution(KDefine.SCREEN_WIDTH,
            KDefine.SCREEN_HEIGHT, false);
}
	//상태를 갱신한다

	public override void Update()
	{
		base.Update();

		if (Input.GetKeyDown(KeyCode.Escape))
		{
#if !UNITY_EDITOR && UNITY_ANDROID
		
			var oJSONObject = new SimpleJSON.JSONClass();
			oJSONObject["Title"] = "알림";
			oJSONObject["Message"] = "메시지";
			oJSONObject["OKButtonTitle"] = "확인";
			oJSONObject["CancelButtonTitle"] = "취소";


			CUnityMessageSender.Instance.SendMessage("ShowAlert", "",
			(a_oCommand, a_oMessage) =>
			{
				bool isQuit = bool.Parse(a_oMessage);

				if (isQuit)
				{	
					Application.Quit();
				}
			});
#else
			Application.Quit();
#endif
		}
	}

	//! UI 카메라를 설정한다
	protected virtual void SetupUICamera()
    {
		if(CSceneManager.UICamera != null) {
			var oUICamera = CSceneManager.UICamera;
			oUICamera.orthographic = true;
			oUICamera.orthographicSize = (KDefine.SCREEN_HEIGHT / 2.0f) * KDefine.UNIT_SCALE;
		}
    }

    //! 메인 카메라를 설정한다
    protected virtual void SetupMainCamera()
    {
		if(CSceneManager.MainCamera != null) {
			var oMainCamera = CSceneManager.MainCamera;
			oMainCamera.orthographic = false;
			oMainCamera.fieldOfView = 0.0f;

			float fDepth = Mathf.Abs(oMainCamera.transform.position.z);
			float fFieldOfView = Mathf.Atan(((KDefine.SCREEN_HEIGHT / 2.0f) * KDefine.UNIT_SCALE) / fDepth);

			oMainCamera.fieldOfView = (fFieldOfView * 2.0f) * Mathf.Rad2Deg;
		}
    }
}
