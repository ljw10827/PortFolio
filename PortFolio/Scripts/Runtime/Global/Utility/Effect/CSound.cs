using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 사운드
public class CSound : CComponent
{
	private AudioSource m_oAudioSource = null;

	//! 볼륨 프로퍼티
	public float Volume
	{
		get
		{
			return m_oAudioSource.volume;
		} set
		{
			m_oAudioSource.volume = value;
		}
	}

	//! 음소거 프로퍼티
	public bool Mute
	{
		get
		{
			return m_oAudioSource.mute;
		} set
		{
			m_oAudioSource.mute = value;
		}
	}

	//! 재생 여부 프로퍼티
	public bool IsPlaying
	{
		get
		{
			return m_oAudioSource.isPlaying;
		}
	}

	//! 초기화
	public override void Awake()
	{
		base.Awake();

		m_oAudioSource = Function.AddComponent<AudioSource>(this.gameObject);
		m_oAudioSource.playOnAwake = false;
	}

	//! 사운드를 재생한다
	public void PlaySound(string a_oFilepath, bool a_bIsLoop, bool a_bIs3DSound)
	{
		m_oAudioSource.clip = CResourceManager.Instance.GetAudioClipForKey(a_oFilepath);
		m_oAudioSource.loop = a_bIsLoop;
		m_oAudioSource.spatialBlend = a_bIs3DSound ? 1.0f : 0.0f;

		m_oAudioSource.Play();
	}

	//! 사운드를 정지한다
	public void PauseSound()
	{
		m_oAudioSource.Pause();
	}

	//! 사운드를 중지한다
	public void StopSound()
	{
		m_oAudioSource.Stop();
	}
}
