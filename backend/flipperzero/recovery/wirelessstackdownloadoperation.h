#pragma once

#include "abstractrecoveryoperation.h"

class QTimer;
class QIODevice;

namespace Flipper {
namespace Zero {

class WirelessStackDownloadOperation : public AbstractRecoveryOperation
{
    Q_OBJECT

    enum State {
        StartingFUS = AbstractOperation::User,
        DeletingWirelessStack,
        DownloadingWirelessStack,
        UpgradingWirelessStack,
        CheckingWirelessStack
    };

public:
    WirelessStackDownloadOperation(Recovery *recovery, QIODevice *file, uint32_t targetAddress = 0, QObject *parent = nullptr);
    const QString description() const override;

private slots:
    void advanceOperationState() override;
    void onOperationTimeout() override;

private:
    void startFUS();
    void deleteWirelessStack();
    bool isWirelessStackDeleted();
    void downloadWirelessStack();
    void upgradeWirelessStack();
    bool isWirelessStackUpgraded();
    bool isWirelessStackOK();
    void tryAgain();

    QIODevice *m_file;
    QTimer *m_loopTimer;
    uint32_t m_targetAddress;
    int m_retryCount;
};

}
}
