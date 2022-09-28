/*
 * ark -- archiver for the KDE project
 *
 * Copyright (C) 2007 Henrique Pinto <henrique.pinto@kdemail.net>
 * Copyright (C) 2008 Harald Hvaal <haraldhv@stud.ntnu.no>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES ( INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION ) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * ( INCLUDING NEGLIGENCE OR OTHERWISE ) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EXTRACTIONDIALOG_H
#define EXTRACTIONDIALOG_H

#include "kerfuffle_export.h"

#include <QDialog>
#include <QUrl>

#include <KFileWidget>

namespace Kerfuffle
{
class KERFUFFLE_EXPORT ExtractionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExtractionDialog(QWidget *parent = nullptr);
    ~ExtractionDialog() override;

    void setShowSelectedFiles(bool);
    void setExtractToSubfolder(bool);
    void setPreservePaths(bool);
    void batchModeOption();
    void setOpenDestinationFolderAfterExtraction(bool);
    void setCloseAfterExtraction(bool);
    void setAutoSubfolder(bool value);

    bool extractAllFiles() const;
    bool openDestinationAfterExtraction() const;
    bool closeAfterExtraction() const;
    bool extractToSubfolder() const;
    bool autoSubfolders() const;
    bool preservePaths() const;
    QUrl destinationDirectory() const;
    QString subfolder() const;

public Q_SLOTS:
    void setBusyGui();
    void setReadyGui();
    void setSubfolder(const QString& subfolder);
    void setCurrentUrl(const QUrl &url);
    void restoreWindowSize();

private Q_SLOTS:
    void writeSettings();
    void slotAccepted();

private:
    void loadSettings();

    class ExtractionDialogUI *m_ui;
    KFileWidget *fileWidget;
};
}

#endif // EXTRACTIONDIALOG_H
