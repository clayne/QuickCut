
#pragma once

#include "QuickCutShared/Managers/ProfileManager.h"
#include "QuickCutShared/Managers/PreferenceManager.h"

#include <QtWidgets/QMainWindow>
#include "ui_MainView.h"

class ExamplesView;
class UpdatesView;
class AboutView;
class ActionView;
class QLocalSocket;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget * parent = nullptr);
    ~MainView();

    void connectSlots();

    void initThemes();
    void initPreference();
    void initProfiles();
    void activateHook();

    bool loadProfiles();
    bool reloadProfiles();
    bool saveProfiles();

    bool sendReloadProfiles();

    void showEvent(QShowEvent * event) override;

public slots:

    void      onProfileSelChange(int index);
    void      onBtnSetActiveProfile();
    void      onBtnDeleteProfile();
    Profile * onBtnCreateProfile();

    void onActionSelChange(int index);
    void onActionDoubleClicked(const QModelIndex & index);
    void onBtnActionCreate();
    void onBtnActionDelete();
    void onBtnActionDuplicate();
    void onBtnActionMoveDown();
    void onBtnActionMoveUp();

    void listItemSwap(QListWidget * list, bool moveUp);

    void onActionSaved();
    void onActionCreated(const Action & action);

    void onReloadProfilesResponse();

    // File Menu
    void onActionFileOpen();
    void onActionFileSave();
    void onActionFileSaveAs();
    void onActionFileRestartService();
    void onActionFileExit();

    void onActionViewToolBar();
    void onActionViewStatusBar();
    void onActionViewRefresh();

    void onActionHelpAbout();
    void onActionHelpExamples();
    void onActionHelpCheckUpdates();

    void onActionLoadTheme(QCTheme::ThemeType type);
    void onActionLoadTheme(const QString & qssPath, QAction * action = nullptr);
    void onLoadCustomStylesheet();

private:
    Ui::MainView * ui;

    QPointer<ActionView>   m_ActionView;
    QPointer<AboutView>    m_AboutView;
    QPointer<UpdatesView>  m_UpdatesView;
    QPointer<ExamplesView> m_ExamplesView;

    QMap<QCTheme::ThemeType, QAction *> m_ThemeActions;

    ProfileManager    m_Profiles;
    PreferenceManager m_Preference;

    QLocalSocket * m_LocalSocket;
    QDataStream    m_SocketStreamIn;
    int            m_SocketBlockSize;
};
