using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 리소스 관리자
public class CResourceManager : CSingleton<CResourceManager>
{
	private Dictionary<string, Shader> m_oShaderList = null;
	private Dictionary<string, Sprite> m_oSpriteList = null;
	private Dictionary<string, Texture> m_oTextureList = null;
	private Dictionary<string, Material> m_oMaterialList = null;
	private Dictionary<string, AudioClip> m_oAudioClipList = null;
	private Dictionary<string, GameObject> m_oGameObjectList = null;
	private Dictionary<string, RuntimeAnimatorController> m_oRuntimeAnimatorControllerList = null;

	//! 초기화
	public override void Awake()
	{
		base.Awake();

		m_oShaderList = new Dictionary<string, Shader>();
		m_oSpriteList = new Dictionary<string, Sprite>();
		m_oTextureList = new Dictionary<string, Texture>();
		m_oMaterialList = new Dictionary<string, Material>();
		m_oAudioClipList = new Dictionary<string, AudioClip>();
		m_oGameObjectList = new Dictionary<string, GameObject>();
		m_oRuntimeAnimatorControllerList = new Dictionary<string, RuntimeAnimatorController>();
	}

	//! 쉐이더를 반환한다
	public Shader GetShaderForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate && 
			!m_oShaderList.ContainsKey(a_oFilepath))
		{
			var oShader = Shader.Find(a_oFilepath);
			m_oShaderList.Add(a_oFilepath, oShader);
		}

		return m_oShaderList[a_oFilepath];
	}

	//! 스프라이트를 반환한다
	public Sprite GetSpriteForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate &&
			!m_oSpriteList.ContainsKey(a_oFilepath))
		{
			var oSprite = Resources.Load<Sprite>(a_oFilepath);
			m_oSpriteList.Add(a_oFilepath, oSprite);
		}

		return m_oSpriteList[a_oFilepath];
	}

	//! 텍스처를 반환한다
	public Texture GetTextureForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate && 
			!m_oTextureList.ContainsKey(a_oFilepath))
		{
			var oTexture = Resources.Load<Texture>(a_oFilepath);
			m_oTextureList.Add(a_oFilepath, oTexture);
		}

		return m_oTextureList[a_oFilepath];
	}

	//! 재질을 반환한다
	public Material GetMaterialForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate &&
			!m_oMaterialList.ContainsKey(a_oFilepath))
		{
			var oMaterial = Resources.Load<Material>(a_oFilepath);
			m_oMaterialList.Add(a_oFilepath, oMaterial);
		}

		return m_oMaterialList[a_oFilepath];
	}

	//! 사본 재질을 반환한다
	public Material GetCopiedMaterialForKey(string a_oFilepath, bool a_bIsAutoCreat = true)
	{
		var oMaterial = this.GetMaterialForKey(a_oFilepath, a_bIsAutoCreat);
		return new Material(oMaterial);
	}

	//! 오디오 클립을 반환한다
	public AudioClip GetAudioClipForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate &&
			!m_oAudioClipList.ContainsKey(a_oFilepath))
		{
			var oAudioClip = Resources.Load<AudioClip>(a_oFilepath);
			m_oAudioClipList.Add(a_oFilepath, oAudioClip);
		}

		return m_oAudioClipList[a_oFilepath];
	}

	//! 게임 객체를 반환한다
	public GameObject GetObjectForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if (a_bIsAutoCreate &&
			!m_oGameObjectList.ContainsKey(a_oFilepath))
		{
			var oGameObject = Resources.Load<GameObject>(a_oFilepath);
			m_oGameObjectList.Add(a_oFilepath, oGameObject);
		}

		return m_oGameObjectList[a_oFilepath];
	}

	//! 애니메이터 컨트롤러를 반환한다
	public RuntimeAnimatorController GetAnimatorControllerForKey(string a_oFilepath, bool a_bIsAutoCreate = true)
	{
		if(a_bIsAutoCreate &&
			!m_oRuntimeAnimatorControllerList.ContainsKey(a_oFilepath))
		{
			var oAnimatorController = Resources.Load<RuntimeAnimatorController>(a_oFilepath);
			m_oRuntimeAnimatorControllerList.Add(a_oFilepath, oAnimatorController);
		}

		return m_oRuntimeAnimatorControllerList[a_oFilepath];
	}
}
