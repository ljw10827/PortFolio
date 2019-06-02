using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

//! 사운드 관리자
public class CSoundManager : CSingleton<CSoundManager>
{
	private bool m_bEffectMute = false;
	private bool m_bBackgroundMute = false;

	private float m_fEffectVolume = 1.0f;
	private float m_fBackgroundVolume = 1.0f;

	private CSound m_oBackgroundSound = null;
	private Dictionary<string, List<CSound>> m_oEffectSoundList = null;

	//! 효과음 볼륨 프로퍼티
	public float EffectVolume
	{
		get
		{
			return m_fEffectVolume;
		} set
		{
			m_fEffectVolume = value;

			this.EnumerateEffectSoundList((a_oSound) =>
			{
				a_oSound.Volume = value;
			});
		}
	}

	//! 배경음 볼륨 프로퍼티
	public float BackgroundVolume
	{
		get
		{
			return m_oBackgroundSound.Volume;
		} set
		{
			m_fBackgroundVolume = value;
			m_oBackgroundSound.Volume = value;
		}
	}

	//! 효과음 음소거 프로퍼티
	public bool EffectMute
	{
		get
		{
			return m_bEffectMute;
		} set
		{
			m_bEffectMute = value;

			this.EnumerateEffectSoundList((a_oSound) =>
			{
				a_oSound.Mute = value;
			});
		}
	}

	//! 배경음 음소거 프로퍼티
	public bool BackgroundMute
	{
		get
		{
			return m_bBackgroundMute;
		} set
		{
			m_bBackgroundMute = value;
			m_oBackgroundSound.Mute = value;
		}
	}

	//! 초기화
	public override void Awake()
	{
		base.Awake();

		m_oEffectSoundList = new Dictionary<string, List<CSound>>();
		m_oBackgroundSound = Function.CreateGameObject<CSound>("BackgroundSound", this.gameObject);
	}

	//! 효과음을 재생한다
	public void PlayOneshotSound(string a_oFilepath, Vector3 a_stPosition)
	{
		var oAudioClip = CResourceManager.Instance.GetAudioClipForKey(a_oFilepath);
		AudioSource.PlayClipAtPoint(oAudioClip, a_stPosition);
	}

	//! 효과음을 재생한다
	public void PlayEffectSound(string a_oFilepath, bool a_bIsLoop = false, bool a_bIs3DSound = false)
	{
		var oSound = this.FindPlayableEffectSound(a_oFilepath);

		if (oSound != null)
		{
			this.EffectVolume = m_fEffectVolume;
			oSound.PlaySound(a_oFilepath, a_bIsLoop, a_bIs3DSound);
		}
	}

	//! 배경음을 재생한다
	public void PlayBackgroundSound(string a_oFilepath, bool a_bIsLoop = true)
	{
		this.BackgroundVolume = m_fBackgroundVolume;
		m_oBackgroundSound.PlaySound(a_oFilepath, a_bIsLoop, false);
	}

	//! 효과음을 정지한다
	public void PauseEffectSound()
	{
		this.EnumerateEffectSoundList((a_oSound) =>
		{
			a_oSound.PauseSound();
		});
	}

	//! 배경음을 정지한다
	public void PauseBackgroundSound()
	{
		m_oBackgroundSound.PauseSound();
	}

	//! 효과음을 정지한다
	public void StopEffectSound()
	{
		this.EnumerateEffectSoundList((a_oSound) =>
		{
			a_oSound.StopSound();
		});
	}

	//! 배경음을 중지한다
	public void StopBackgroundSound()
	{
		m_oBackgroundSound.StopSound();
	}

	//! 효과음 리스트를 순회한다
	private void EnumerateEffectSoundList(System.Action<CSound> a_oCallback)
	{
		var oKeyList = m_oEffectSoundList.Keys.ToList();

		for (int i = 0; i < oKeyList.Count; ++i)
		{
			string oKey = oKeyList[i];
			var oSoundList = m_oEffectSoundList[oKey];

			for (int j = 0; j < oSoundList.Count; ++j)
			{
				var oSound = oSoundList[j];
				a_oCallback(oSound);
			}
		}
	}

	//! 재생 가능한 효과음을 탐색한다
	private CSound FindPlayableEffectSound(string a_oFilepath)
	{
		if (!m_oEffectSoundList.ContainsKey(a_oFilepath))
		{
			var oTempSoundList = new List<CSound>();
			m_oEffectSoundList.Add(a_oFilepath, oTempSoundList);
		}

		var oSoundList = m_oEffectSoundList[a_oFilepath];

		// 최대 중첩 횟수를 벗어나지 않았을 경우
		if (oSoundList.Count < KDefine.MAX_NUM_DUPLICATE_EFFECT_SOUND)
		{
			var oSound = Function.CreateGameObject<CSound>("EffectSound", this.gameObject);
			oSoundList.Add(oSound);

			return oSound;
		}
		else
		{
			for (int i = 0; i < oSoundList.Count; ++i)
			{
				var oSound = oSoundList[i];

				if (!oSound.IsPlaying)
				{
					return oSound;
				}
			}
		}

		return null;
	}
}
