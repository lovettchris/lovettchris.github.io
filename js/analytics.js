// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

var siteConsent = null;
var telemetryInitialized = false;

function addTelemetryTag() {
    if (!telemetryInitialized) {
        telemetryInitialized = true;
    }
}

function wcp_ready(err, _siteConsent){
    if (err != undefined) {
        return error;
    } else {
        siteConsent = _siteConsent;
        onConsentChanged();
    }
}

function onConsentChanged() {
    var userConsent = siteConsent.getConsentFor(WcpConsent.consentCategories.Analytics);
    if (!siteConsent.isConsentRequired){
        // force the dialog just for testing...
        // todo: remove this when we are done testing...
        siteConsent.manageConsent();
    }
    else if(userConsent) {
        addTelemetryTag();
    }
    else {
        // todo: disable telemetry!
    }
}

$(document).ready(function () {
    WcpConsent.init("en-US", "cookie-banner", wcp_ready, onConsentChanged);
});
