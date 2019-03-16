#pragma once

#include "ab/util/FlagsEnum.hpp"
//#include "widgets/helper/ScrollbarHighlight.hpp"

#include <QTime>
#include <cinttypes>
#include <memory>
#include <vector>

namespace chatterino
{
    class MessageElement;

    enum class MessageFlag : uint16_t {
        None = 0,
        System = (1 << 0),
        Timeout = (1 << 1),
        Highlighted = (1 << 2),
        DoNotTriggerNotification = (1 << 3),  // disable notification sound
        Centered = (1 << 4),
        Disabled = (1 << 5),
        DisableCompactEmotes = (1 << 6),
        Collapsed = (1 << 7),
        ConnectedMessage = (1 << 8),
        DisconnectedMessage = (1 << 9),
        Untimeout = (1 << 10),
        PubSub = (1 << 11),
        Subscription = (1 << 12),
        Notification = (1 << 13),
    };
    using MessageFlags = ab::FlagsEnum<MessageFlag>;

    struct Message
    {
        Message();
        ~Message();

        // Making this a mutable means that we can update a messages flags,
        // while still keeping Message constant. This means that a message's
        // flag can be updated without the renderer being made aware, which
        // might be bad. This is a temporary effort until we can figure out what
        // the right const-correct way to deal with this is.
        mutable MessageFlags flags;
        QTime parseTime;
        QString id;
        QString searchText;
        QString loginName;
        QString displayName;
        QString localizedName;
        QString timeoutUser;
        uint32_t count = 1;
        std::vector<std::unique_ptr<MessageElement>> elements;

        // ScrollbarHighlight getScrollBarHighlight() const;
    };

    using MessagePtr = std::shared_ptr<const Message>;

}  // namespace chatterino