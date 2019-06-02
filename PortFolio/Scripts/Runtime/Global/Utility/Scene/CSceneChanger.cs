using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

//! 씬 전환자
public class CSceneChanger : CSingleton<CSceneChanger>
{
	//! 씬을 제거한다
	public void RemoveScene(ESceneIndex a_eSceneIndex,
		System.Action<AsyncOperation, bool> a_oCallback)
	{
		var oScenePath = SceneUtility.GetScenePathByBuildIndex((int)a_eSceneIndex);
		this.RemoveScene(oScenePath, a_oCallback);
	}

	//! 씬을 제거한다
	public void RemoveScene(string a_oSceneName,
		System.Action<AsyncOperation, bool> a_oCallback)
	{
		var oSceneManager = CSceneManager.CurrentSceneManager;
		oSceneManager.StartCoroutine(this.DoRemoveScene(a_oSceneName, a_oCallback));
	}
	
	//! 씬을 전환한다
	public void ChangeScene(ESceneIndex a_eSceneIndex,
		System.Action<AsyncOperation, bool> a_oCallback,
		float a_fDelay = 0.0f,
		LoadSceneMode a_eLoadSceneMode = LoadSceneMode.Single)
	{
		var oScenePath = SceneUtility.GetScenePathByBuildIndex((int)a_eSceneIndex);
		this.ChangeScene(oScenePath, a_oCallback, a_fDelay, a_eLoadSceneMode);
	}

	//! 씬을 전환한다
	public void ChangeScene(string a_oSceneName,
		System.Action<AsyncOperation, bool> a_oCallback,
		float a_fDelay = 0.0f,
		LoadSceneMode a_eLoadSceneMode = LoadSceneMode.Single)
	{
		var oSceneManager = CSceneManager.CurrentSceneManager;
		
		// 씬을 전환한다
		oSceneManager.StartCoroutine(this.DoChangeScene(a_oSceneName,
			a_oCallback,
			a_fDelay,
			a_eLoadSceneMode));
	}

	//! 씬을 제거한다
	private IEnumerator DoRemoveScene(string a_oSceneName,
		System.Action<AsyncOperation, bool> a_oCallback)
	{
		var oAsyncOperation = SceneManager.UnloadSceneAsync(a_oSceneName);
		yield return Function.WaitAsyncOperation(oAsyncOperation, a_oCallback);
	}

	//! 씬을 전환한다
	private IEnumerator DoChangeScene(string a_oSceneName,
		System.Action<AsyncOperation, bool> a_oCallback,
		float a_fDelay,
		LoadSceneMode a_eLoadSceneMode)
	{
		yield return new WaitForSeconds(a_fDelay);

		var oAsyncOperation = SceneManager.LoadSceneAsync(a_oSceneName, a_eLoadSceneMode);
		yield return Function.WaitAsyncOperation(oAsyncOperation, a_oCallback);
	}
}
