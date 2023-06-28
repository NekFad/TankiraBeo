#include <iostream>
#include <string>
#include <Windows.h>
#include <Lmcons.h>
#include <fstream>
#include <WinReg.h>
#pragma comment(lib, "urlmon.lib")
#pragma execution_character_set( "utf-8" ) // Enable Unicode
#define MAX_LOCATION_LEN 250 // Max Character of Game Location Variable
using namespace std;

int PlayGame();
int MigrateLauncher();

void editValue(string path1, string valueReg, string valueName) {
    HKEY hKey;
    LPCSTR lpSubKey = path1.c_str();
    LPCSTR lpValueName = valueName.c_str();
    LPCSTR lpData = valueReg.c_str();
    DWORD dwDataSize = strlen(lpData);

    if (RegOpenKeyExA(HKEY_CURRENT_USER, lpSubKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
    {
        if (RegSetValueExA(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpData, dwDataSize) == ERROR_SUCCESS)
        {
            printf("SetValue Thành công!\n", lpData);
        }
        else
        {
            printf("Lỗi ARRL-REG2: Không thể setValue của Value đó \n");
        }

        RegCloseKey(hKey);
    }
    else
    {
        printf("Lỗi ARRL-REG1: Không thể mở Key \n");
    }
}

int main()
{
    SetConsoleOutputCP(65001); // Enable Unicode
    system("title Aurora Launcher"); // Set Title App
    system("color b"); // Set Color Text
    system("mkdir Game >nul 2>&1");

    char username[UNLEN + 1]; // ---------------------------- Get Current Username - I
    DWORD username_len = UNLEN + 1; // ---------------------------- Get Current Username - II
    GetUserNameA(username, &username_len); // ---------------------------- Get Current Username - III
    char NPath[MAX_PATH]; // ---------------------------- Get Current Directory - I
    GetCurrentDirectoryA(MAX_PATH, NPath); // -------------------- Get Current Directory - II
    string GameDir = "\\Game"; // -------------------- Variable - GameDir
    string GameLoc = NPath + GameDir;
    string LuaChon;

    cout << endl;
    cout << "   ==================================================================================================================" << endl;
    cout << "    Xin chào! " << username << endl;
    cout << "    Thư mục Launcher: " << NPath << endl;
    cout << "    Thư mục game: " << GameLoc << endl;
    cout << "   ==================================================================================================================" << endl;
    cout << endl;
    cout << "    [1] Bắt đầu chơi" << endl;
    cout << "    [2] Chuyển về Launcher khác" << endl;
    cout << "    [X] Thoát" << endl;
    cout << endl;
    cout << "                                              Nhập lựa chọn của bạn > ";
    cin >> LuaChon;

    if (LuaChon == "1")
    {
        PlayGame();
    }
    else {
        cout << "Lỗi ARRL2" << endl;
    }
    if (LuaChon == "2")
    {
        MigrateLauncher();
    }
    else {
        cout << "Lỗi ARRL2" << endl;
    }
}

int PlayGame()
{
    system("cls");
    char NPath[MAX_PATH]; // ---------------------------- Get Current Directory - I
    GetCurrentDirectoryA(MAX_PATH, NPath); // -------------------- Get Current Directory - II
    string GameDir = "\\Game"; // -------------------- Variable - GameDir
    string GameLoc = NPath + GameDir;
    string SAMPExe = "\\samp.exe";
    string SAMPLoc = GameLoc + SAMPExe;
    string GTAExe = "\\gta_sa.exe";
    string URLDown = "https://raw.githubusercontent.com/Tankira/P-AuroraLauncher/main/samp.zip";
    string IMPFile = "\\samp.zip"; // ---------------- Name file can thiet
    string IMPLoc = GameLoc + IMPFile; // ---------------- Location file can thiet
    string username;

    cout << "Đang kiểm tra các file cần thiết, vui lòng chờ!" << endl;
    ifstream file;
    file.open("CheckConfirm");
    if (file)
    {
        system("cls");
        cout << "Nhập tên nhân vật của bạn [Ten_Ho]: ";
        cin >> username;
        editValue("Software\\SAMP", username, "PlayerName");
        editValue("Software\\SAMP", GameLoc + GTAExe, "gta_sa_exe");
        system((SAMPLoc + " thay cai nay thanh ip server cua ban").c_str());
        system("pause");
    }
    else
    {
        cout << "Không tìm thấy file CheckConfirm" << endl;
        cout << "Đang tải file cần thiết, vui lòng chờ!" << endl;
        URLDownloadToFileA(NULL, URLDown.c_str(), IMPLoc.c_str(), 0, NULL);
        system("tar -xf ""Game\\samp.zip"" -C ""Game");
        system("del /s /q ""Game\\samp.zip""");
        system("echo Yes > CheckConfirm | attrib +h CheckConfirm");
        cout << "Tải thành công!" << endl;
        system("cls");
        cout << "Nhập tên nhân vật của bạn [Ten_Ho]: ";
        cin >> username;
        editValue("Software\\SAMP", username, "PlayerName");
        editValue("Software\\SAMP", GameLoc + GTAExe, "gta_sa_exe");
        system((SAMPLoc + " thay cai nay thanh ip server cua ban").c_str());
        system("exit");
    }
    return 0;
}

int MigrateLauncher() 
{
    string gtaexe = "\\gta_sa.exe";
    string path;

    system("cls");
    cout << " Nhập đường dẫn thư mục chứa game [ VD: D:\\Dulieu\\Game\\GTA Online ]: ";
    cin.ignore();
    getline(cin, path);
    editValue("Software\\SAMP", path + gtaexe, "gta_sa_exe");
    cout << "Chuyển Launcher thành công!" << endl;
    system("timeout /t 2 -nobreak >nul");
    system("cls");
    main();
    return 0;
}
