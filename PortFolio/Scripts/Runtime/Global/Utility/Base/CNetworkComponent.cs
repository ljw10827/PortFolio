using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class CNetworkComponent : NetworkBehaviour
{
	[HideInInspector] public Transform m_oTransform = null;
	[HideInInspector] public Rigidbody m_oRigidbody = null;

	//! 초기화
	public virtual void Awake()
	{
		m_oTransform = this.GetComponent<Transform>();
		m_oRigidbody = this.GetComponent<Rigidbody>();
	}

	public virtual void Start()
	{
		//DO NOTHING
	}

	//! 상태를 갱신한다
	public virtual void Update()
	{
		// Do Nothing
	}

	//! 상태를 지연 갱신한다
	public virtual void LateUpdate()
	{
		// Do Nothing
	}
}
