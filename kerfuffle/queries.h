/*
 * ark -- archiver for the KDE project
 *
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

#ifndef QUERIES_H
#define QUERIES_H

#include "kerfuffle_export.h"

#include <QCheckBox>
#include <QString>
#include <QHash>
#include <QWaitCondition>
#include <QMutex>
#include <QVariant>

namespace Kerfuffle
{

typedef QHash<QString, QVariant> QueryData;

class KERFUFFLE_EXPORT Query
{
public:
    /**
     * Execute the response. It needs to be called from the GUI thread.
     */
    virtual void execute() = 0;

    /**
     * Will block until the response have been set.
     * Useful for worker threads that need to show a dialog.
     */
    void waitForResponse();

    QVariant response() const;

protected:
    /**
     * Protected constructor
     */
    Query();
    virtual ~Query() {}

    void setResponse(const QVariant &response);

    QueryData m_data;

private:
    QWaitCondition m_responseCondition;
    QMutex m_responseMutex;
};

/* *****************************************************************
 * Used to query the user if an existing file should be overwritten.
 * *****************************************************************
 */
class KERFUFFLE_EXPORT OverwriteQuery : public Query
{
public:
    explicit OverwriteQuery(const QString& filename);
    void execute() override;
    bool responseCancelled();
    bool responseOverwriteAll();
    bool responseOverwrite();
    bool responseRename();
    bool responseSkip();
    bool responseAutoSkip();
    QString newFilename();

    void setNoRenameMode(bool enableNoRenameMode);
    bool noRenameMode();
    void setMultiMode(bool enableMultiMode);
    bool multiMode();
private:
    bool m_noRenameMode;
    bool m_multiMode;
};

/* **************************************
 * Used to query the user for a password.
 * **************************************
 */
class KERFUFFLE_EXPORT PasswordNeededQuery : public Query
{
public:
    explicit PasswordNeededQuery(const QString& archiveFilename, bool incorrectTryAgain = false);
    void execute() override;

    bool responseCancelled();
    QString password();
};

/* *************************************************************
 * Used to query the user if a corrupt archive should be loaded.
 * *************************************************************
 */
class KERFUFFLE_EXPORT LoadCorruptQuery : public Query
{
public:
    explicit LoadCorruptQuery(const QString& archiveFilename);
    void execute() override;

    bool responseYes();
};

class KERFUFFLE_EXPORT ContinueExtractionQuery : public Query
{
public:
    explicit ContinueExtractionQuery(const QString& error, const QString& archiveEntry);
    void execute() override;

    bool responseCancelled();
    bool dontAskAgain();
private:
    QCheckBox m_chkDontAskAgain;
};

}

#endif /* ifndef QUERIES_H */
