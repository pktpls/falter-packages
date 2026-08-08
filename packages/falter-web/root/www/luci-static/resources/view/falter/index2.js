'use strict';
'require rpc';
'require view';

const callFalterStatus = rpc.declare({
  object: 'falter',
  method: 'status',
  expect: { '': {} }
});

// Detect whether a password has been set for the root account.
// Do it the easy way by checking if Luci rendered the warning alert.
// Our CSS hides this alert from our users so they use our own password flow.
function isPasswordAbsent() {
  const sel = '.warning:has(a.btn[href*="/admin/system/admin"])';
  return document.querySelectorAll(sel).length > 0;
}

return view.extend({
  passwordAbsent: isPasswordAbsent(),

  load() {
    return L.resolveDefault(callFalterStatus());
  },

  render(falterStatus) {
    return E([], [
      E('h1', {}, _('Hello, world!')),
      E('pre', {}, `status: ${falterStatus.status}`),
      E('pre', {}, `passwordAbsent: ${(this.passwordAbsent)}`)
    ]);
  },

  handleReset: null,
  handleSave: null,
  handleSaveApply: null,

});
