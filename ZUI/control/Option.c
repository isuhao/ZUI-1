﻿#include <ZUI.h>




ZEXPORT ZuiAny ZCALL ZuiOptionProc(ZuiInt ProcId, ZuiControl cp, ZuiOption p, ZuiAny Param1, ZuiAny Param2, ZuiAny Param3) {
	switch (ProcId)
	{
	case Proc_CoreInit:
		return 0;
	case Proc_OnCreate: {
		p = (ZuiOption)malloc(sizeof(ZOption));
		memset(p, 0, sizeof(ZOption));
		//保存原来的回调地址,创建成功后回调地址指向当前函数
		//创建继承的控件 保存数据指针
		p->old_udata = ZuiButtonProc(Proc_OnCreate, cp, 0, 0, 0, 0);
		p->old_call = (ZCtlProc)&ZuiButtonProc;

		return p;
	}
		break;
	case Proc_OnEvent: {
		TEventUI *event= (TEventUI *)Param1;
		switch (event->Type)
		{
		case ZEVENT_LBUTTONUP: {
			ZuiControlCall(Proc_Option_SetSelected, cp, !ZuiControlCall(Proc_Option_GetSelected, cp, NULL, NULL, NULL), NULL, NULL);
			ZuiControlInvalidate(cp);
			break;
		}
		default:
			break;
		}
		break;
	}
	case Proc_OnPaint:{
		ZuiGraphics gp = (ZuiGraphics)Param1;
		RECT *rc = &cp->m_rcItem;
		if (p->m_bSelected) {
			ZuiImage img;
			if (((ZuiButton)p->old_udata)->type == 0) {
				if (p->m_ResSelected) {
					img = p->m_ResSelected->p;
					ZuiDrawImageEx(gp, img, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, 0, 0, img->Width, img->Height, 255);
				}
				else {
					ZuiDrawFillRect(gp, ARGB(200, 0, 3, 255), rc->left, rc->top, rc->right - rc->left - 1, rc->bottom - rc->top - 1);
				}
			}
			else if (((ZuiButton)p->old_udata)->type == 1) {
				if (p->m_ResSelectedHot) {
					img = p->m_ResSelectedHot->p;
					ZuiDrawImageEx(gp, img, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, 0, 0, img->Width, img->Height, 255);
				}
				else {
					ZuiDrawFillRect(gp, ARGB(200, 0, 255, 255), rc->left, rc->top, rc->right - rc->left - 1, rc->bottom - rc->top - 1);
				}
			}
			else if (((ZuiButton)p->old_udata)->type == 2) {
				if (p->m_ResSelectedPushed) {
					img = p->m_ResSelectedPushed->p;
					ZuiDrawImageEx(gp, img, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, 0, 0, img->Width, img->Height, 255);
				}
				else {
					ZuiDrawFillRect(gp, ARGB(200, 255, 255, 255), rc->left, rc->top, rc->right - rc->left - 1, rc->bottom - rc->top - 1);
				}
			}
			return 0;//选择状态下不由按钮控件绘制
		}
		break;
	}
	case Proc_Option_SetSelected: {
		if (p->m_bSelected == Param1) return;
		p->m_bSelected = Param1;


		ZuiControlNotify(L"selectchanged", cp, NULL, NULL, NULL);
		break;
	}
	case Proc_Option_GetSelected: {
		return p->m_bSelected;
	}
	case Proc_Option_SetResSelected: {
		if (p->m_ResSelected)
			ZuiResDBDelRes(p->m_ResSelected);
		p->m_ResSelected = Param1;
		break;
	}
	case Proc_Option_SetResSelectedHot: {
		if (p->m_ResSelectedHot)
			ZuiResDBDelRes(p->m_ResSelectedHot);
		p->m_ResSelectedHot = Param1;
		break;
	}
	case Proc_Option_SetResSelectedPushed: {
		if (p->m_ResSelectedPushed)
			ZuiResDBDelRes(p->m_ResSelectedPushed);
		p->m_ResSelectedPushed = Param1;
		break;
	}
	case Proc_SetAttribute: {
		if (_tcscmp(Param1, _T("selected")) == 0) ZuiControlCall(Proc_Option_SetSelected, cp, wcscmp(Param2, L"true") == 0 ? TRUE : FALSE, NULL, NULL);
		else if (_tcscmp(Param1, _T("selectedimage")) == 0) ZuiControlCall(Proc_Option_SetResSelected, cp, ZuiResDBGetRes(Param2, ZREST_IMG), NULL, NULL);
		else if (_tcscmp(Param1, _T("selectedhotimage")) == 0) ZuiControlCall(Proc_Option_SetResSelectedHot, cp, ZuiResDBGetRes(Param2, ZREST_IMG), NULL, NULL);
		else if (_tcscmp(Param1, _T("selectedpushedimage")) == 0) ZuiControlCall(Proc_Option_SetResSelectedPushed, cp, ZuiResDBGetRes(Param2, ZREST_IMG), NULL, NULL);
		break;
	}
	case Proc_OnInit:{
		break;
	}
	default:
		break;
	}
	return p->old_call(ProcId, cp, p->old_udata, Param1, Param2, Param3);
}



