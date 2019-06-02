using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 이벤트 디스패처
public class CEventDispatcher : CComponent
{
	public System.Action<GameObject, string> EventHandler { get; set; }

	//! 이벤트를 수신했을 경우
	public void OnReceiveEvent(string a_oEventName)
	{
		if (this.EventHandler != null)
		{
			this.EventHandler(this.gameObject, a_oEventName);
		}
	}
}
