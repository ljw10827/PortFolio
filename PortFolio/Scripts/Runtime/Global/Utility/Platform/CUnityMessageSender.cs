using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CUnityMessageSender : CSingleton<CUnityMessageSender>
{
#if !UNITY_EDITOR && UNITY_ANDROID
	private AndroidJavaObject m_oJavaObject = null;
#endif

	public override void Awake()
	{
		base.Awake();
#if !UNITY_EDITOR && UNITY_ANDROID
		var oJavaClass = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		m_oJavaObject = oJavaClass.GetStatic<AndroidJavaObject>("currentActivity");
		//연동준비끝
#endif

	}

	//메시지를 전송한다.
	public void SendMessage(string a_oCommand, string a_oMessage, 
				System.Action<string, string> a_oCallback = null, bool a_bIsAutoRemove = true)
	{
		if (a_oCallback != null)
		{
			var oCallbackInfo = new KeyValuePair<bool, System.Action<string, string>>(a_bIsAutoRemove, a_oCallback);
			CDeviceMessageReceiver.Instance.AddCallbackInfo(a_oCommand, oCallbackInfo);
		}

#if !UNITY_EDITOR && UNITY_ANDROID
		m_oJavaObject.Call("handleUnityMessage", a_oCommand, a_oMessage);
#endif
	}
}
