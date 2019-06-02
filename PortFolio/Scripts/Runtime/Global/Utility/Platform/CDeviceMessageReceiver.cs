using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//타입 재정의(typedef)
using TCallbackInfo = System.Collections.Generic.KeyValuePair<bool, System.Action<string, string>>;

public class CDeviceMessageReceiver : CSingleton<CDeviceMessageReceiver>
{
	private Dictionary<string, TCallbackInfo> m_oCallbackInfoList = null;

	public override void Awake()
	{
		base.Awake();
		m_oCallbackInfoList = new Dictionary<string, TCallbackInfo>();
	}

	//콜백 정보 추가
	public void AddCallbackInfo(string a_oKey, TCallbackInfo a_oCallbackInfo)
	{
		if (!m_oCallbackInfoList.ContainsKey(a_oKey))
		{
			m_oCallbackInfoList.Add(a_oKey, a_oCallbackInfo);
		}
	}


	//콜백 정보 제거
	public void RemoveCallbackInfo(string a_oKey)
	{
		if(m_oCallbackInfoList.ContainsKey(a_oKey))
		{
			m_oCallbackInfoList.Remove(a_oKey);
		}
	}

	// 디바이스 메세지를 처리한다.
	public void HandleDeviceMessage(string a_oMessage)
	{
		//TODO : 디바이스 메세지 처리 로직 구현
		var oJSONObject = SimpleJSON.JSON.Parse(a_oMessage);

		string oCommand = oJSONObject["Command"];
		string oMessage = oJSONObject["Message"];

		if (m_oCallbackInfoList.ContainsKey(oCommand))
		{
			var oCallbackInfo = m_oCallbackInfoList[oCommand];
			oCallbackInfo.Value(oCommand, oMessage);

			if (oCallbackInfo.Key)
			{
				this.RemoveCallbackInfo(oCommand);
			}

		}
	}


}
