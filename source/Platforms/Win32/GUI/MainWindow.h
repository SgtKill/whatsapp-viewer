#pragma once

#include <windows.h>
#include <vector>

#include "ListViewSorting.h"
#include "OpenDatabaseDialog.h"
#include "../Objects/Accelerator.h"

class AboutDialog;
class ChatExporter;
class Exception;
class ImageDecoder;
class Settings;
class WhatsappChat;
class WhatsappMessage;
class WhatsappDatabase;
class WhatsAppViewer;

enum SortingDirection
{
	SORTING_DIRECTION_ASCENDING,
	SORTING_DIRECTION_DESCENDING
};

class MainWindow
{
private:
	WhatsAppViewer &whatsAppViewer;
	ImageDecoder &imageDecoder;
	Settings &settings;
	HWND dialog;
	AboutDialog *aboutDialog;
	Accelerator accelerator;
	std::vector<WhatsappChat *> chats;
	WhatsappDatabase *database;
	std::string tempFilename;
	OpenDatabaseStruct lastDatabaseOpened;
	int sortingColumn;
	SortingDirection sortingDirection;

	void openDatabase();
	void openPlainDatabase(const std::string &filename);
	void closeDatabase();

	void decryptDatabaseCrypt5();
	void decryptDatabaseCrypt7();
	void decryptDatabaseCrypt8();
	void clearChats();
	void clearChatList();

	void createChildWindows();
	void setIcon();
	void resizeChildWindows(int width, int height);
	void addChats();
	void addChat(WhatsappChat &chat);
	void selectChat(WhatsappChat *chat);
	void sortChats();
	void setSortingColumn(int columnIndex);
	void updateSortingArrow();

	bool saveFileDialog(std::string &filename, const std::string &suggestion, const std::string &filter);
	void exportChat(WhatsappChat &chat, ChatExporter &exporter, const std::string &extension);
	void exportChatToTxt(WhatsappChat &chat);
	void exportChatToHtml(WhatsappChat &chat);

	void getTempFilename();
	bool fileExists(const std::string &filename);

	void readSettings();

	void showAboutDialog();
	void close();

	void onDrop(HDROP drop);

	void searchChats();

	static INT_PTR CALLBACK dialogCallback(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);
	INT_PTR handleMessage(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam);

	static int CALLBACK sortingCallback(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

public:
	MainWindow(WhatsAppViewer &whatsAppViewer, ImageDecoder &imageDecoder);
	~MainWindow();

	bool handleMessages();
	void openDatabase(const std::string &filename);

	static void displayException(HWND mainWindow, Exception &exception);
};
