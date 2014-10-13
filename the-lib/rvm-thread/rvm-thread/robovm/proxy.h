/*
 * Copyright (C) 2012 Trillian Mobile AB
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ROBOVM_PROXY_H
#define ROBOVM_PROXY_H

typedef void (*ProxyHandler)(Env*, Object*, ProxyMethod*, jvalue*, jvalue*);

extern jboolean rvmInitProxy(Env* env);
extern Class* rvmProxyCreateProxyClass(Env* env, Class* superclass, ClassLoader* classLoader, char* className, jint interfacesCount, Class** interfaces, 
	jint instanceDataSize, jint instanceDataOffset, unsigned short instanceRefCount, ProxyHandler handler);

#endif
