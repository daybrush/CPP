// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include "Log.h"
#include <crtdbg.h>

#ifndef __DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
