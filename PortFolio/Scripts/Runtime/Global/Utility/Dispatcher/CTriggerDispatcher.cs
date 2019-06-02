using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 접촉 이벤트 디스패처
public class CTriggerDispatcher : CComponent
{
	public System.Action<GameObject, Collider> TriggerEnter { get; set; }
	public System.Action<GameObject, Collider> TriggerStay { get; set; }
	public System.Action<GameObject, Collider> TriggerExit { get; set; }

	//! 접촉이 발생했을 경우
	public void OnTriggerEnter(Collider a_oCollider)
	{
		if (this.TriggerEnter != null)
		{
			this.TriggerEnter(this.gameObject, a_oCollider);
		}
	}

	//! 접촉 중일 경우
	public void OnTriggerStay(Collider a_oCollider)
	{
		if (this.TriggerStay != null)
		{
			this.TriggerStay(this.gameObject, a_oCollider);
		}
	}

	//! 접촉이 끝났을 경우
	public void OnTriggerExit(Collider a_oCollider)
	{
		if (this.TriggerExit != null)
		{
			this.TriggerExit(this.gameObject, a_oCollider);
		}
	}
}
