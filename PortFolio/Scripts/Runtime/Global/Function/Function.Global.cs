using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 전역 함수
public static partial class Function
{
    //! 로그를 출력한다
    public static void ShowLog(string a_oFormat, 
        params object[] a_oParams)
    {
        string oLog = string.Format(a_oFormat, a_oParams);
        Debug.Log(oLog);
    }

	//! 함수를 지연 호출한다
	public static void LateCall(System.Action<object[]> a_oCallback, 
		float a_fDelay,
		params object[] a_oParams)
	{
		var oSceneManager = CSceneManager.CurrentSceneManager;
		oSceneManager.StartCoroutine(Function.DoLateCall(a_oCallback, a_fDelay, a_oParams));
	}

	//! 비동기 연산을 대기한다
	public static IEnumerator WaitAsyncOperation(AsyncOperation a_oAsyncOperation,
		System.Action<AsyncOperation, bool> a_oCallback)
	{
		a_oAsyncOperation.completed += (a_oSender) =>
		{
			if (a_oCallback != null)
			{
				a_oCallback(a_oSender, true);
			}
		};

		// 비동기 연산을 처리한다
		while (!a_oAsyncOperation.isDone)
		{
			yield return new WaitForEndOfFrame();

			if (a_oCallback != null)
			{
				a_oCallback(a_oAsyncOperation, false);
			}
		}
	}
	
	//! 컴포넌트를 추가한다
	public static T AddComponent<T>(GameObject a_oGameObject) where T : Component
	{
		var oComponent = a_oGameObject.GetComponent<T>();

		if (oComponent == null)
		{
			oComponent = a_oGameObject.AddComponent<T>();
		}

		return oComponent;
	}

	//! 컴포넌트를 탐색한다
	public static T FindComponent<T>(string a_oName) where T : Component
	{
		var oGameObject = GameObject.Find(a_oName);
		
		if(oGameObject == null) {
			return null;
		}
		
		return oGameObject.GetComponentInChildren<T>();
	}

	//! 게임 객체를 생성한다
	public static GameObject CreateGameObject(string a_oName, 
		GameObject a_oParent,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false)
	{
		var oGameObject = new GameObject(a_oName);

		if (a_oParent != null)
		{
			oGameObject.transform.SetParent(a_oParent.transform, a_bIsWorldStay);
		}

		if (a_bIsResetTransform)
		{
			oGameObject.transform.localPosition = Vector3.zero;
			oGameObject.transform.localEulerAngles = Vector3.zero;
			oGameObject.transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
		}

		return oGameObject;
	}

	//! 사본 게임 객체를 생성한다
	public static GameObject CreateCopiedGameObject(string a_oName,
		GameObject a_oOriginObject,
		GameObject a_oParentObject,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false)
	{
		var oGameObject = Object.Instantiate(a_oOriginObject, 
			Vector3.zero, Quaternion.identity);

		if (a_oParentObject != null)
		{
			oGameObject.transform.SetParent(a_oParentObject.transform, a_bIsWorldStay);

			if (!a_bIsResetTransform)
			{
				oGameObject.transform.localPosition = a_oOriginObject.transform.localPosition;
				oGameObject.transform.localEulerAngles = a_oOriginObject.transform.localEulerAngles;
			}
		}

		if (a_bIsResetTransform)
		{
			oGameObject.transform.localPosition = Vector3.zero;
			oGameObject.transform.localEulerAngles = Vector3.zero;
			oGameObject.transform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
		}

		oGameObject.name = a_oName;
		return oGameObject;
	}

	//! 사본 게임 객체를 생성한다
	public static GameObject CreateCopiedGameObject(string a_oName,
		string a_oObjectFilepath,
		GameObject a_oParentObject,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false)
	{
		var oOriginObject = CResourceManager.Instance.GetObjectForKey(a_oObjectFilepath);
		return Function.CreateCopiedGameObject(a_oName, oOriginObject, a_oParentObject, a_bIsWorldStay, a_bIsResetTransform);
	}

	//! 게임 객체를 생성한다
	public static T CreateGameObject<T>(string a_oName,
		GameObject a_oParent,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false) where T : Component
	{
		var oGameObject = Function.CreateGameObject(a_oName,
			a_oParent,
			a_bIsWorldStay,
			a_bIsResetTransform);

		return Function.AddComponent<T>(oGameObject);
	}

	//! 사본 게임 객체를 생성한다
	public static T CreateCopiedGameObject<T>(string a_oName,
		GameObject a_oOriginObject,
		GameObject a_oParentObject,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false) where T : Component
	{
		var oGameObject = Function.CreateCopiedGameObject(a_oName,
			a_oOriginObject,
			a_oParentObject,
			a_bIsWorldStay,
			a_bIsResetTransform);

		return oGameObject.GetComponentInChildren<T>();
	}

	//! 사본 게임 객체를 생성한다
	public static T CreateCopiedGameObject<T>(string a_oName,
		string a_oObjectFilepath,
		GameObject a_oParentObject,
		bool a_bIsWorldStay = false,
		bool a_bIsResetTransform = false) where T : Component
	{
		var oGameObject = Function.CreateCopiedGameObject(a_oName,
			a_oObjectFilepath,
			a_oParentObject,
			a_bIsWorldStay,
			a_bIsResetTransform);

		return oGameObject.GetComponentInChildren<T>();
	}

	//! 함수를 지연 호출한다
	private static IEnumerator DoLateCall(System.Action<object[]> a_oCallback, 
		float a_fDelay,
		params object[] a_oParams)
	{
		yield return new WaitForSeconds(a_fDelay);
		a_oCallback(a_oParams);
	}
}
