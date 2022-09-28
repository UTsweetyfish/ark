/*
 * Copyright (c) 2016 Vladyslav Batyrenko <mvlabat@gmail.com>
 * Copyright (c) 2016 Elvis Angelaccio <elvis.angelaccio@kde.org>
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

#ifndef ABSTRACTADDTEST_H
#define ABSTRACTADDTEST_H

#include "archive_kerfuffle.h"
#include "pluginmanager.h"

/**
 * Base class for tests about Add/Copy/Move jobs.
 * Make sure to call the constructor in order to load the plugins.
 */
class AbstractAddTest : public QObject
{
    Q_OBJECT

public:

    static QStringList getEntryPaths(Kerfuffle::Archive *archive);

    /**
     * Setup test cases for each format and for each plugin.
     * @param testName Name of the test case shown in the debug output
     * @param archiveName Archive name. The extension of the tested formats will be appended to it.
     * @param targetEntries Entries passed to the job.
     * @param destination Destination entry passed to the job.
     * @param expectedNewPaths New expected paths that the job should create.
     * @param numberOfEntries Number of entries in the archive expected after the job ends.
     */
    void setupRows(const QString &testName, const QString &archiveName, const QVector<Kerfuffle::Archive::Entry*> &targetEntries, Kerfuffle::Archive::Entry *destination, const QStringList &expectedNewPaths, uint numberOfEntries) const;

protected:

    Kerfuffle::PluginManager m_pluginManager;
};

#endif //ABSTRACTADDTEST_H
