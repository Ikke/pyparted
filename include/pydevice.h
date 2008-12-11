/*
 * pydevice.h
 * pyparted type definitions for pydevice.c
 *
 * Copyright (C) 2007  Red Hat, Inc.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions of
 * the GNU General Public License v.2, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY expressed or implied, including the implied warranties of
 * MERCHANTABILITY or FITNESS FOR A * PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.  You should have received a copy of the
 * GNU General Public License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.  Any Red Hat trademarks that are incorporated in the
 * source code or documentation are not subject to the GNU General Public
 * License and may only be used or replicated with the express permission of
 * Red Hat, Inc.
 *
 * Red Hat Author(s): David Cantrell <dcantrell@redhat.com>
 */

#ifndef PYDEVICE_H_INCLUDED
#define PYDEVICE_H_INCLUDED

#include <Python.h>
#include <structmember.h>

#include <parted/parted.h>

/* 1:1 function mappings for device.h in libparted */
PyObject *py_ped_device_probe_all(PyObject *s, PyObject *args);
PyObject *py_ped_device_free_all(PyObject *s, PyObject *args);
PyObject *py_ped_device_get(PyObject *s, PyObject *args);
PyObject *py_ped_device_get_next(PyObject *s, PyObject *args);
PyObject *py_ped_device_is_busy(PyObject *s, PyObject *args);
PyObject *py_ped_device_open(PyObject *s, PyObject *args);
PyObject *py_ped_device_close(PyObject *s, PyObject *args);
PyObject *py_ped_device_destroy(PyObject *s, PyObject *args);
PyObject *py_ped_device_cache_remove(PyObject *s, PyObject *args);
PyObject *py_ped_device_begin_external_access(PyObject *s, PyObject *args);
PyObject *py_ped_device_end_external_access(PyObject *s, PyObject *args);
PyObject *py_ped_device_read(PyObject *s, PyObject *args);
PyObject *py_ped_device_write(PyObject *s, PyObject *args);
PyObject *py_ped_device_sync(PyObject *s, PyObject *args);
PyObject *py_ped_device_sync_fast(PyObject *s, PyObject *args);
PyObject *py_ped_device_check(PyObject *s, PyObject *args);
PyObject *py_ped_device_get_constraint(PyObject *s, PyObject *args);

PyDoc_STRVAR(device_get_next_doc,
"get_next(self) -> Device\n\n"
"Return the next Device in the list detected by _ped.device_probe_all().");

PyDoc_STRVAR(device_is_busy_doc,
"is_busy(self) -> bool\n\n"
"Return True if this Device is currently in use, False otherwise.");

PyDoc_STRVAR(device_open_doc,
"open(self) -> bool\n\n"
"Attempt to open this Device to allow use of read(), write(), and sync()\n"
"methods.  The open() call is architecture-dependent.  Apart from\n"
"requesting access to the device from the operating system, it does things\n"
"flushing caches.\n\n"
"This method may allocate internal resources depending on the architecture\n"
"All allocated resources are freed when you call the close() method.\n\n"
"Return True if the Device could be opened, False otherwise.");

PyDoc_STRVAR(device_close_doc,
"close(self) -> bool\n\n"
"Close this Device.  All allocated resources are freed.  If a failure\n"
"occurs while closing the Device, this method returns False.  The method\n"
"returns True on success.");

PyDoc_STRVAR(device_destroy_doc,
"destroy(self) -> None\n\n"
"Destroys the Device, removes it from the device list, destroys all\n"
"allocated resources associated with it, and destroys the object.");

PyDoc_STRVAR(device_cache_remove_doc,
"cache_remove(self) -> None\n\n"
"Remove the Device from the device list, but does not destroy it or any\n"
"allocated resources associated with it.  USE WITH CAUTION.");

PyDoc_STRVAR(device_begin_external_access_doc,
"begin_external_accessself() -> bool\n\n"
"Begins external access mode for this Device.  External access mode allows\n"
"you to safely do I/O on the device.  If a Device is open, then you should\n"
"not do any I/O on that Device, e.g. by calling an external program like\n"
"e2fsck, unless you put it in external access mode.  You should not use\n"
"any commands that do I/O to a Device while it is in external access mode.\n\n"
"Also, you should not close a Device while it is in external access mode.\n\n"
"Return True if the Device was successfully put in external access mode,\n"
"False otherwise.");

PyDoc_STRVAR(device_end_external_access_doc,
"end_external_access(self) -> bool\n\n"
"Ends external access mode for this Device.  Returns True on success,\n"
"False on failure.");

PyDoc_STRVAR(device_read_doc,
"read(self, buffer, start, count) -> bool\n\n"
"Read count sectors from this Device in to buffer, starting at sector start.\n"
"Both start and count are long integers and buffer is a Python object large\n"
"enough to hold what you want to read.\n\n"
"Return True if the read was successful, False otherwise.");

PyDoc_STRVAR(device_write_doc,
"write(self, buffer, start, count) -> bool\n\n"
"Write count sectors from buffer to this Device, starting at sector start.\n"
"Both start and count are long integers and buffer is a Python object holding\n"
"what you want to write to this Device.\n\n"
"Return True if the write was successful, False otherwise.");

PyDoc_STRVAR(device_sync_doc,
"sync(self) -> bool\n\n"
"Flushes all write-behind caches that might be holding up writes.  It is\n"
"slow because it guarantees cache coherency among all relevant caches.\n"
"Return True on success, False otherwise.");

PyDoc_STRVAR(device_sync_fast_doc,
"sync_fast(self) -> bool\n\n"
"Flushes all write-behind caches that might be holding writes.  WARNING:\n"
"Does NOT ensure cache coherency with other caches.  If you need cache\n"
"coherency, use sync() instead.  Return True on success, False otherwise.");

PyDoc_STRVAR(device_check_doc,
"check(self) -> long int\n\n"
"Architecture-dependent function that returns the number of sectors on\n"
"this Device that are ok.");

PyDoc_STRVAR(device_get_constraint_doc,
"get_constraint(self) -> Constraint\n\n"
"Get a Constraint that represents hardware requirements on alignment and\n"
"geometry.  This is, for example, import for media that have a physical\n"
"sector size that is a multiple of the logical sector size.");

/* _ped.CHSGeometry type is the Python equiv of PedCHSGeometry in libparted */
typedef struct {
    PyObject_HEAD

    /* a PedCHSGeometry stores three ints */
    int cylinders;
    int heads;
    int sectors;
} _ped_CHSGeometry;

void _ped_CHSGeometry_dealloc(_ped_CHSGeometry *self);
int _ped_CHSGeometry_traverse(_ped_CHSGeometry *self, visitproc visit, void *arg);
int _ped_CHSGeometry_clear(_ped_CHSGeometry *self);
PyObject *_ped_CHSGeometry_get(_ped_CHSGeometry *self, void *closure);
int _ped_CHSGeometry_set(_ped_CHSGeometry *self, PyObject *value,
                         void *closure);

PyDoc_STRVAR(_ped_CHSGeometry_doc,
"A _ped.CHSGeometry object describes a disk using the older CHS style\n"
"of defining disk geometry.  CHS stands for cylinders-heads-sectors.\n\n"
"The _ped.CHSGeometry objects are created automatically when devices are\n"
"probed by libparted.  They are used for reference purposes to get the\n"
"number of cylinders, heads, or sectors on a disk.  They cannot be used\n"
"to change the CHS values on a device.");

extern PyTypeObject _ped_CHSGeometry_Type_obj;

/* _ped.Device type is the Python equivalent of PedDevice in libparted */
typedef struct {
    PyObject_HEAD

    /* a PedDevice is complex, we will store primitives when appropriate or
     * just other Python objects we've created for the typedefs in libparted */
    char *model;
    char *path;
    long long type;
    long long sector_size;
    long long phys_sector_size;
    long long length;             /* PedSector */
    int open_count;
    int read_only;
    int external_mode;
    int dirty;
    int boot_dirty;
    PyObject *hw_geom;            /* a _ped.CHSGeometry */
    PyObject *bios_geom;          /* a _ped.CHSGeometry */
    short host;
    short did;
} _ped_Device;

void _ped_Device_dealloc(_ped_Device *self);
int _ped_Device_traverse(_ped_Device *self, visitproc visit, void *arg);
int _ped_Device_clear(_ped_Device *self);
PyObject *_ped_Device_get(_ped_Device *self, void *closure);
int _ped_Device_set(_ped_Device *self, PyObject *value, void *closure);

PyDoc_STRVAR(_ped_Device_doc,
"A _ped.Device object describes a block device accessible via the\n"
"operating system.  On Linux, an example block device is /dev/sda.\n\n"
"It is important to note that _ped.Device objects describe entire\n"
"block devices and not just partitions.");

extern PyTypeObject _ped_Device_Type_obj;

#endif /* PYDEVICE_H_INCLUDED */

/* vim:tw=78:ts=4:et:sw=4
 */
